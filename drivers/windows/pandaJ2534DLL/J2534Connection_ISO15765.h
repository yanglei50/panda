#pragma once
#include <string>
#include "J2534Connection.h"
#include "J2534Connection_CAN.h"
#include "MessageTx_ISO15765.h"
#include "MessageRx.h"

class MessageTx_ISO15765;

typedef struct {
	std::string dispatched_msg;
	std::string remaining_payload;
} PRESTAGED_WRITE;

class J2534Connection_ISO15765 : public J2534Connection {
public:
	J2534Connection_ISO15765(
		std::shared_ptr<PandaJ2534Device> panda_dev,
		unsigned long ProtocolID,
		unsigned long Flags,
		unsigned long BaudRate
	);

	virtual long PassThruWriteMsgs(PASSTHRU_MSG *pMsg, unsigned long *pNumMsgs, unsigned long Timeout);

	virtual long PassThruStartMsgFilter(unsigned long FilterType, PASSTHRU_MSG * pMaskMsg, PASSTHRU_MSG * pPatternMsg, PASSTHRU_MSG * pFlowControlMsg, unsigned long * pFilterID);

	int get_matching_out_fc_filter_id(const std::string & msgdata, unsigned long flags, unsigned long flagmask);

	int get_matching_in_fc_filter_id(const J2534Frame& msg, unsigned long flagmask = CAN_29BIT_ID);

	virtual void processMessageReceipt(const J2534Frame& msg);
	virtual void processMessage(const J2534Frame& msg);

	virtual unsigned long getMinMsgLen() {
		return 4;
	}

	virtual unsigned long getMaxMsgLen() {
		return 4099;
	};

	virtual bool _is_29bit() {
		return (this->Flags & CAN_29BIT_ID) == CAN_29BIT_ID;
	}

	virtual bool isProtoCan() {
		return TRUE;
	}

private:
	std::array<std::shared_ptr<MessageRx>, 10> rxConversations;
};
