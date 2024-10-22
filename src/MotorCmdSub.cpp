#include "NodeHandler.h"
#include "Motor.pb.h"
#include "Power.pb.h"
#include <sys/time.h>

std::mutex mutex_;
timeval currentTime;

void motor_cmd_cb(motor_msg::MotorCmdStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "[INFO] [" << currentTime.tv_sec << "." << currentTime.tv_usec << "]: ";
    std::cout << "Received MotorCmd, " << "Time Stamp: " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    mutex_.unlock();
}

int main() {
    // Subscriber //
    core::NodeHandler nh;
    core::Rate rate(1000);
    core::Subscriber<motor_msg::MotorCmdStamped> &sub_motor_cmd = nh.subscribe<motor_msg::MotorCmdStamped>("motor/command", 1000, motor_cmd_cb);
    
    // While forever //
    while (1)
    {
        core::spinOnce();
        std::cout << rate.sleep() << " << sleep" << "\n";
    }
    return 0;
}
