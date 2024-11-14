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

void motor_state_cb(motor_msg::MotorStateStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "=====" << "MotorState" << "=====" << "\n";
    std::cout << "Header  : " << msg.header().seq() << "\n";
    std::cout << "  Time Stamp : " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    std::cout << "Module A: " << "\n";
    std::cout << "  Theta    : " << msg.module_a().theta() << "\n";
    std::cout << "  Beta     : " << msg.module_a().beta() << "\n";
    std::cout << "  current_r: " << msg.module_a().current_r() << "\n";
    std::cout << "  current_l: " << msg.module_a().current_l() << "\n";
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
    std::cout << "Mode   : " << msg.robot_mode() << "\n";
    std::cout << "Receive Time: " << currentTime.tv_sec << "." << currentTime.tv_usec << "\n";
    mutex_.unlock();
}

void power_state_cb(power_msg::PowerStateStamped msg) {
    mutex_.lock();
    gettimeofday(&currentTime, nullptr);
    std::cout << "=====" << "PowerState" << "=====" << "\n";
    std::cout << "Header : " << msg.header().seq() << "\n";
    std::cout << "  Time Stamp : " << msg.header().stamp().sec() << "." << msg.header().stamp().usec() << "\n";
    std::cout << "Digital: " << msg.digital() << "\n";
    std::cout << "V 0    : " << msg.v_0() << "\n";
    std::cout << "I 0    : " << msg.i_0() << "\n";
    std::cout << "V 1    : " << msg.v_1() << "\n";
    std::cout << "I 1    : " << msg.i_1() << "\n";    
    std::cout << "V 2    : " << msg.v_2() << "\n";
    std::cout << "I 2    : " << msg.i_2() << "\n";    
    std::cout << "V 3    : " << msg.v_3() << "\n";
    std::cout << "I 3    : " << msg.i_3() << "\n";    
    std::cout << "V 4    : " << msg.v_4() << "\n";
    std::cout << "I 4    : " << msg.i_4() << "\n";    
    std::cout << "V 5    : " << msg.v_5() << "\n";
    std::cout << "I 5    : " << msg.i_5() << "\n";    
    std::cout << "V 6    : " << msg.v_6() << "\n";
    std::cout << "I 6    : " << msg.i_6() << "\n";    
    std::cout << "V 7    : " << msg.v_7() << "\n";
    std::cout << "I 7    : " << msg.i_7() << "\n";
    std::cout << "V 8    : " << msg.v_8() << "\n";
    std::cout << "I 8    : " << msg.i_8() << "\n";
    std::cout << "V 9    : " << msg.v_9() << "\n";
    std::cout << "I 9    : " << msg.i_9() << "\n";
    std::cout << "V 10   : " << msg.v_10() << "\n";
    std::cout << "I 10   : " << msg.i_10() << "\n";
    std::cout << "V 11   : " << msg.v_11() << "\n";
    std::cout << "I 11   : " << msg.i_11() << "\n";
    std::cout << "Receive Time: " << currentTime.tv_sec << "." << currentTime.tv_usec << "\n";
    mutex_.unlock();
}

int main() {
    // Subscriber //
    core::NodeHandler nh;
    core::Rate rate(1000);
    core::Subscriber<motor_msg::MotorCmdStamped> &sub_motor_cmd = nh.subscribe<motor_msg::MotorCmdStamped>("motor/command", 1000, motor_cmd_cb);
    core::Subscriber<motor_msg::MotorStateStamped> &sub_motor_state = nh.subscribe<motor_msg::MotorStateStamped>("motor/state", 1000, motor_state_cb);
    core::Subscriber<power_msg::PowerCmdStamped> &sub_power_cmd = nh.subscribe<power_msg::PowerCmdStamped>("power/command", 1000, power_cmd_cb);
    core::Subscriber<power_msg::PowerStateStamped> &sub_power_state = nh.subscribe<power_msg::PowerStateStamped>("power/state", 1000, power_state_cb);
    
    // While forever //
    while (1)
    {
        core::spinOnce();
        std::cout << rate.sleep() << " << sleep" << "\n";
    }
    return 0;
}
