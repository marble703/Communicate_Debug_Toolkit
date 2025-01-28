#include "visualization_tool_node.hpp"
#include <QApplication>
#include "widget.h"
#include <thread>
#include <std_msgs/msg/char.hpp>
visualization_node::visualization_node():
rclcpp::Node("visualization_node"){
    Serial_info_sub = this->create_subscription<communicate_2025::msg::SerialInfo>(
        "/shoot_info", rclcpp::SensorDataQoS(), std::bind(&visualization_node::Serial_info_callback, this, std::placeholders::_1 ));
    Autoaim_sub = this->create_subscription<communicate_2025::msg::Autoaim>(
        "/communicate/debug/autoaim", rclcpp::SensorDataQoS(), std::bind(&visualization_node::Autoaim_callback, this, std::placeholders::_1 ));

    
}


void visualization_node::Serial_info_callback(const communicate_2025::msg::SerialInfo::SharedPtr msg ){
    RCLCPP_INFO(this->get_logger(), "processing_serial_info");
    this->w.ui.down_yaw_editor->setText(QString::number(msg->yaw));
    this->w.ui.down_pitch_editor->setText(QString::number(msg->pitch));
    
    this->w.ui.down_find_bool_editor->setText([&msg]()->QString{
        QString qstr = QString(QChar(static_cast<unsigned char>(msg->is_find.data)));
        return qstr;
    }());

}

void visualization_node::Autoaim_callback(const communicate_2025::msg::Autoaim::SharedPtr msg ){
    RCLCPP_INFO(this->get_logger(), "processing_autoaim");
    this->w.ui.up_yaw_editor->setText(QString::number(msg->yaw));
    this->w.ui.up_pitch_editor->setText(QString::number(msg->pitch));
    
    this->w.ui.up_enemy_color_editor->setText(QString::number(msg->enemy_team_color));
    this-> w.ui.up_mode_editor->setText(QString::number(msg->mode));
    this->w.ui.up_rune_flag_editor->setText(QString::number(msg->rune_flag));
    
}




int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    QApplication a(argc, argv);  
    auto node = std::make_shared<visualization_node>();
    node->w.show();  // 在主线程显示 Widget

    // 启动 ROS2 的异步线程
    std::thread ros_thread([node]() {
        rclcpp::spin(node);
    });

    // 主线程运行 Qt 事件循环
    int result = a.exec();

    // 清理
    rclcpp::shutdown();
    ros_thread.join();
    return result;
}