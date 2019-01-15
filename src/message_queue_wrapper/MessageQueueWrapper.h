#ifndef AHRS_MESSAGEQUEUEWRAPPER_H
#define AHRS_MESSAGEQUEUEWRAPPER_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <memory>
#include <vector>
#include <string>

namespace communication
{
    class MessageQueueWrapper
    {
    public:
        MessageQueueWrapper(const std::string &name);
        MessageQueueWrapper(const std::string &name, uint32_t  queueLength, uint32_t messageQueueSize);
        ~MessageQueueWrapper() = default;

        void send(const std::vector<uint8_t>& msg) const ;
        std::vector<uint8_t> receive() const;

    private:
        std::shared_ptr<boost::interprocess::message_queue> messageQueue_;

        std::string name_;
        uint32_t queueLength_;
        uint32_t messageQueueSize_;
    };
}

#endif