#include "cv_connection.hpp"

#include <opencv2/opencv.hpp>
#include <vector>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
	
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

OpenCVConnector::OpenCVConnector() : it(nh), counter(0)	{
   pub = it.advertise("camera/image", 1);
}


void OpenCVConnector::WriteToOpenCV(cv::Mat img) {

    cv_bridge::CvImage img_bridge;
    sensor_msgs::Image img_msg; // >> message to be sent

    std_msgs::Header header; // empty header
    header.seq = counter; // user defined counter
    header.stamp = ros::Time::now(); // time
    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::MONO8, img);
    img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image
    std::cout << "pub image" << std::endl;
    pub.publish(img_msg); // ros::Publisher pub_img = node.advertise<sensor_msgs::Image>("topic", queuesize);

}


