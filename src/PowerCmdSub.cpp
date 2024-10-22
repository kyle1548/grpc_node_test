#include "NodeHandler.h"
#include "Motor.pb.h"
#include "Power.pb.h"
#include <sys/time.h>

std::mutex mutex_;
timeval currentTime;

void power_cmd_cb(power_msg::PowerCmdStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "[INFO] [" << currentTime.tv_sec << "." << currentTime.tv_usec << "]: ";
    std::cout << "Received PowerCmd, " << "Time Stamp: " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    mutex_.unlock();
}


int main() {
    // Subscriber //
    core::NodeHandler nh;
    core::Rate rate(1000);
    core::Subscriber<power_msg::PowerCmdStamped> &sub_power_cmd = nh.subscribe<power_msg::PowerCmdStamped>("power/command", 1000, power_cmd_cb);
    
    // While forever //
    while (1)
    {
        core::spinOnce();
        std::cout << rate.sleep() << " << sleep" << "\n";
    }
    return 0;
}
