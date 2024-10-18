#include "NodeHandler.h"
#include "Motor.pb.h"
#include "Power.pb.h"
#include <sys/time.h>

std::mutex mutex_;
timeval currentTime;

void motor_cmd_cb(motor_msg::MotorCmdStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "=====" << "MotorCmd" << "=====" << "\n";
    std::cout << "Header  : " << msg.header().seq() << "\n";
    std::cout << "  Time Stamp : " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    std::cout << "Module A: " << "\n";
    std::cout << "  Theta: " << msg.module_a().theta() << "\n";
    std::cout << "  Beta : " << msg.module_a().beta() << "\n";
    std::cout << "  kp   : " << msg.module_a().kp() << "\n";
    std::cout << "  ki   : " << msg.module_a().ki() << "\n";
    std::cout << "  kd   : " << msg.module_a().kd() << "\n";
    std::cout << "Receive Time: " << currentTime.tv_sec << "." << currentTime.tv_usec << "\n";
    mutex_.unlock();
}

void power_cmd_cb(power_msg::PowerCmdStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "=====" << "PowerCmd" << "=====" << "\n";
    std::cout << "Header : " << msg.header().seq() << "\n";
    std::cout << "  Time Stamp : " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    std::cout << "Digital: " << msg.digital() << "\n";
    std::cout << "Power  : " << msg.power() << "\n";
    std::cout << "Mode   : " << msg.motor_mode() << "\n";
    std::cout << "Receive Time: " << currentTime.tv_sec << "." << currentTime.tv_usec << "\n";
    mutex_.unlock();
}


int main() {
    // Subscriber //
    core::NodeHandler nh;
    core::Rate rate(1000);
    core::Subscriber<motor_msg::MotorCmdStamped> &sub_motor_cmd = nh.subscribe<motor_msg::MotorCmdStamped>("motor/command", 1000, motor_cmd_cb);
    core::Subscriber<power_msg::PowerCmdStamped> &sub_power_cmd = nh.subscribe<power_msg::PowerCmdStamped>("power/command", 1000, power_cmd_cb);
    
    // While forever //
    while (1)
    {
        core::spinOnce();
        std::cout << rate.sleep() << " << sleep" << "\n";
    }
    return 0;
}
