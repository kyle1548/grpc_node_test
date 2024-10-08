#include "NodeHandler.h"
#include "Motor.pb.h"
#include "Power.pb.h"
#include <sys/time.h>

int main() {
    // Publisher //
    core::NodeHandler nh;
    core::Rate rate(1000);
    core::Publisher<motor_msg::MotorCmdStamped> &pub_motor_cmd = nh.advertise<motor_msg::MotorCmdStamped>("Motor/command");
    core::Publisher<motor_msg::MotorStateStamped> &pub_motor_state = nh.advertise<motor_msg::MotorStateStamped>("Motor/state");
    core::Publisher<power_msg::PowerCmdStamped> &pub_power_cmd = nh.advertise<power_msg::PowerCmdStamped>("Power/command");
    core::Publisher<power_msg::PowerStateStamped> &pub_power_state = nh.advertise<power_msg::PowerStateStamped>("Power/state");
    
    // Motor & Power msg //
    motor_msg::MotorCmdStamped   motor_cmd;
    motor_msg::MotorStateStamped motor_state;
    power_msg::PowerCmdStamped   power_cmd;
    power_msg::PowerStateStamped power_state;
    std::vector< motor_msg::MotorCmd*> modules_cmd = {
        motor_cmd.mutable_module_a(),
        motor_cmd.mutable_module_b(),
        motor_cmd.mutable_module_c(),
        motor_cmd.mutable_module_d()
    };
    std::vector< motor_msg::MotorState*> modules_state = {
        motor_state.mutable_module_a(),
        motor_state.mutable_module_b(),
        motor_state.mutable_module_c(),
        motor_state.mutable_module_d()
    };

    // Initial values //
    int seq = 0;
    double theta = 0.0;
    double beta = 0.0;
    double ki = 50.5;
    double kp = 10.6;
    double kd = 40.7;
    double current_r = 0.7;
    double current_l = 0.7;
    double v = 0.0;
    double i = 0.0;

    // While forever //
    timeval currentTime;
    while (1)
    {
        const auto start = std::chrono::steady_clock::now();
        // Header //
        gettimeofday(&currentTime, nullptr);
        motor_cmd.mutable_header()->set_seq(seq);
        motor_cmd.mutable_header()->mutable_stamp()->set_sec(currentTime.tv_sec);
        motor_cmd.mutable_header()->mutable_stamp()->set_usec(currentTime.tv_usec);
        motor_state.mutable_header()->set_seq(seq);
        motor_state.mutable_header()->mutable_stamp()->set_sec(currentTime.tv_sec);
        motor_state.mutable_header()->mutable_stamp()->set_usec(currentTime.tv_usec);
        power_cmd.mutable_header()->set_seq(seq);
        power_cmd.mutable_header()->mutable_stamp()->set_sec(currentTime.tv_sec);
        power_cmd.mutable_header()->mutable_stamp()->set_usec(currentTime.tv_usec);
        power_state.mutable_header()->set_seq(seq);
        power_state.mutable_header()->mutable_stamp()->set_sec(currentTime.tv_sec);
        power_state.mutable_header()->mutable_stamp()->set_usec(currentTime.tv_usec);
        seq ++;

        // Motor modules //
        for (auto& module : modules_cmd) {
            module->set_theta(theta);
            module->set_beta(beta);
            module->set_ki(ki);
            module->set_kp(kp);
            module->set_kd(kd);
        }
        for (auto& module : modules_state) {
            module->set_theta(theta);
            module->set_beta(beta);
            module->set_current_r(current_r);
            module->set_current_l(current_l);
        }
        theta += 0.1;
        beta += 0.1;
        current_r += 0.1;
        current_l += 0.1;

        // Power //
        bool digital = seq % 2 == 0;
        bool power = seq % 2 == 0;
        int  motor_mode = seq % 5;
        power_cmd.set_digital(digital);
        power_cmd.set_power(power);
        power_cmd.set_motor_mode((power_msg::MOTORMODE)motor_mode);
        power_state.set_digital(digital);
        power_state.set_power(power);
        power_state.set_motor_mode((power_msg::MOTORMODE)motor_mode);

        // Power V & I //
        power_state.set_v_0(v);
        power_state.set_i_0(i);
        power_state.set_v_1(v);
        power_state.set_i_1(i);
        power_state.set_v_2(v);
        power_state.set_i_2(i);
        power_state.set_v_3(v);
        power_state.set_i_3(i);
        power_state.set_v_4(v);
        power_state.set_i_4(i);
        power_state.set_v_5(v);
        power_state.set_i_5(i);
        power_state.set_v_6(v);
        power_state.set_i_6(i);
        power_state.set_v_7(v);
        power_state.set_i_7(i);
        power_state.set_v_8(v);
        power_state.set_i_8(i);
        power_state.set_v_9(v);
        power_state.set_i_9(i);
        power_state.set_v_10(v);
        power_state.set_i_10(i);
        power_state.set_v_11(v);
        power_state.set_i_11(v);
        v += 0.5;
        i += 0.5;

        // Publish //
        std::cout << "MotorCmd   message length\t" << motor_cmd.ByteSizeLong() << "\n";
        std::cout << "MotorState message length\t" << motor_state.ByteSizeLong() << "\n";
        std::cout << "PowerCmd   message length\t" << power_cmd.ByteSizeLong() << "\n";
        std::cout << "PowerState message length\t" << power_state.ByteSizeLong() << "\n";
        pub_motor_cmd.publish(motor_cmd);
        pub_motor_state.publish(motor_state);
        pub_power_cmd.publish(power_cmd);
        pub_power_state.publish(power_state);

        // Using time //
        const auto diff = std::chrono::steady_clock::now() - start;
        std::cout << std::chrono::duration<double>(diff).count() << " seconds\n\n";
        std::cout << rate.sleep() << " << sleep" << "\n";
    }
    return 0;
}
