#ifndef T_SQUARE_CPP
#define T_SQUARE_CPP

#include "T_square.h"
#include "ElaText.h"
#include "ElaMessageBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
T_Square::T_Square(QWidget* parent)
    : ElaWidget(parent)
{
    setWindowTitle("yaw轴自瞄方波发射器");
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    QFont font;
    font.setPointSize(14);
    setFont(font);

    yaw_min_editor = new ElaLineEdit(this);
    yaw_max_editor = new ElaLineEdit(this);
    time_interval = new ElaLineEdit(this);
    yaw_switch = new ElaToggleSwitch(this);

    connect(yaw_switch,&ElaToggleSwitch::toggled,[=](bool checked){
        if(checked){
            if (yaw_min_editor->text().isEmpty() || yaw_max_editor->text().isEmpty() || time_interval->text().isEmpty()){
                ElaMessageBar::error(ElaMessageBarType::PositionPolicy::Top,"警告","获取到的波形参数不完整，请检查输入",0,this);
                yaw_switch->setIsToggled(false);
                return;
            }
            send_flag = true;
            // std::cout<<"send_flag: "<<send_flag<<std::endl;
        }else{
            send_flag = false;
            // std::cout<<"send_flag: "<<send_flag<<std::endl;
        }
    });
    
    ElaText *yaw_min_text = new ElaText("方波最小幅值",this);
    yaw_min_text->setFont(font);
    ElaText *yaw_max_text = new ElaText("方波最大幅值",this);
    yaw_max_text->setFont(font);
    ElaText *time_interval_text = new ElaText("发送时间间隔(单位ms)",this);
    time_interval_text->setFont(font);

    QHBoxLayout *yaw_min_layout = new QHBoxLayout();
    yaw_min_layout->addWidget(yaw_min_text);
    yaw_min_layout->addWidget(yaw_min_editor);
    QHBoxLayout *yaw_max_layout = new QHBoxLayout();
    yaw_max_layout->addWidget(yaw_max_text);
    yaw_max_layout->addWidget(yaw_max_editor);
    QHBoxLayout *time_interval_layout = new QHBoxLayout();
    time_interval_layout->addWidget(time_interval_text);
    time_interval_layout->addWidget(time_interval);
    
    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(yaw_switch);
    main_layout->addLayout(yaw_min_layout);
    main_layout->addLayout(yaw_max_layout);
    main_layout->addLayout(time_interval_layout);
    setLayout(main_layout);
    


}



T_Square::~T_Square()
{
}



#endif // T_SQUARE_CPP