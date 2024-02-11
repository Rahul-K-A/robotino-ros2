from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.actions.set_parameter import SetParameter
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("hostname",
                               default_value = "172.26.1.1",
                               description="Robotino IP Address"),
        Node(
            package='rto_node',
            namespace='rto3',
            executable='rto_node',
            name='rto_core',
            parameters=[{'hostname': LaunchConfiguration("hostname")}],
            remappings=[('/rto_joint_states', '/joint_states')]
        ),
        Node(
            package='rto_node',
            namespace='rto3',
            executable='rto_laserrangefinder_node',
            name='rto_laser',
            parameters=[{'hostname': LaunchConfiguration("hostname")}]
        ),
    ])