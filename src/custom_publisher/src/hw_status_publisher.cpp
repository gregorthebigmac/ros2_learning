#include "rclcpp/rclcpp.hpp"
#include "custom_interface/msg/hardware_status.hpp"

class hardware_status_publisher : public rclcpp::Node {
public:
    hardware_status_publisher() : Node("hardware_status_publisher") {
        pub = this->create_publisher<custom_interface::msg::HardwareStatus>("hardware_status", 10);
        timer = this->create_wall_timer(
                    std::chrono::seconds(1),
                    std::bind(&hardware_status_publisher::publish_hardware_status, this));
        RCLCPP_INFO(this->get_logger(), "Hardware status publisher has been started");
    }

private:
    void publish_hardware_status() {
        auto msg = custom_interface::msg::HardwareStatus();
        msg.some_int = 42;
        msg.this_is_false = true;
        msg.status_msg = "hardware_status_node reporing status: NOMINAL";
        pub->publish(msg);
    }
    rclcpp::Publisher<custom_interface::msg::HardwareStatus>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<hardware_status_publisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
