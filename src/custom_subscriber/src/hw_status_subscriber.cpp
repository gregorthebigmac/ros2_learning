#include "rclcpp/rclcpp.hpp"
#include "custom_interface/msg/hardware_status.hpp"

class hardware_status_subscriber : public rclcpp::Node {
public:
    hardware_status_subscriber() : Node("hardware_status_subscriber") {
        subscriber = this->create_subscription<custom_interface::msg::HardwareStatus>("hardware_status", 10,
            std::bind(&hardware_status_subscriber::callback_hardware_status, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "hardware_status_subscriber has begun.");
    }
private:
    void callback_hardware_status(const custom_interface::msg::HardwareStatus::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "status_msg = %s", msg->status_msg.c_str());
        RCLCPP_INFO(this->get_logger(), "some_int = %d", msg->some_int);
        RCLCPP_INFO(this->get_logger(), "this_is_false = %d", msg->this_is_false);
    }
    rclcpp::Subscription<custom_interface::msg::HardwareStatus>::SharedPtr subscriber;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<hardware_status_subscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
