// All rights complied to VRMonkey

#pragma once

#include "Runtime/Core/Public/Async/AsyncWork.h"
#include "OVR_Platform.h"
#include "OculusIAPCallbackProxy.h"

class FCallbackMessagePoller : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FCallbackMessagePoller>;

	ovrMessageHandle Message = nullptr;


public:

	// Constructor
	FCallbackMessagePoller(ovrMessageType TargetMessageType, FMessageDelegate* TaskDoneDelegate)
	{
		this->MessageType = TargetMessageType;
		this->OnTaskDoneDelegate = TaskDoneDelegate;
	}


protected:

	ovrMessageType MessageType;
	FMessageDelegate* OnTaskDoneDelegate;

	void DoWork()
	{

		UE_LOG(LogTemp, Warning, TEXT("ASYNC MESSAGE POLLING STARTED. TargetMessage=%s"), ANSI_TO_TCHAR(ovrMessageType_ToString(MessageType)));

		// Poll for a response
		while (true)
		{
			if ( (Message = ovr_PopMessage()) == nullptr )
			{
				continue;
			}

			if (OnTaskDoneDelegate->IsBound()) {
				OnTaskDoneDelegate->Execute(Message);
			}
			else
			{
				log("Error: delegate not bound")
			}
			break;
		}
	}


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCallbackMessagePoller, STATGROUP_ThreadPoolAsyncTasks);
	}
};
