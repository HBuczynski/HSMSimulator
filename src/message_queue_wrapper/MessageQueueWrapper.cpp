#include "MessageQueueWrapper.h"

using namespace std;
using namespace communication;
using namespace boost::interprocess;

MessageQueueWrapper::MessageQueueWrapper(const string &name)
    :   name_(name),
        queueLength_(0),
        messageQueueSize_(0)
{
    messageQueue_ = make_shared<message_queue>(open_only, name_.c_str());

    queueLength_ = messageQueue_->get_max_msg();
    messageQueueSize_ = messageQueue_->get_max_msg_size();
}

MessageQueueWrapper::MessageQueueWrapper(const string &name, uint32_t queueLength, uint32_t messageQueueSize)
    :   name_(name),
        queueLength_(queueLength),
        messageQueueSize_(messageQueueSize)
{
    message_queue::remove(name.c_str());
    messageQueue_ = make_shared<message_queue>(create_only,
                                               name.c_str(),
                                               queueLength_,
                                               messageQueueSize);
}

void MessageQueueWrapper::send(const vector<uint8_t> &msg) const
{
    messageQueue_->send(msg.data(), msg.size(), 0);
}

vector<uint8_t> MessageQueueWrapper::receive() const
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    vector<uint8_t> packet(messageQueueSize_);
    messageQueue_->receive(packet.data(), packet.size(), receivedSize, priority);

    return packet;
}