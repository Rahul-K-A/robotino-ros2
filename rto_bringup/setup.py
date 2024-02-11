import os
from glob import glob
from setuptools import setup
package_name = 'rto_bringup'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # ... Other data files
        # Include all launch files.
        ('share/' + package_name, ['launch/rto_bringup_launch.py']), 
        ('share/' + package_name, ['launch/rto_rviz_launch.py']), 
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='rahul',
    maintainer_email='karahul209@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
