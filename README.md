** Simluation ** 
To launch robot model in gazebo:

ros2 launch articubot_one launch_sim.launch.py 

To use the keyboard as input controller:

ros2 run teleop_twist_keyboard teleop_twist_keyboard

To start SLAM_TOOLBOX:

ros2 launch slam_toolbox online_async_launch.py 

Rviz2 config:

Fixed Frame - odometry
Add: 
  TF
  ROBOT MODEL == Description_topic - /robot_discription
  Laser Scan == Topic - /scan
  Map == Topic - /map
