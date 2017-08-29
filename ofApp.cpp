#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->cap.open(1);

	this->frame_img.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) / 2, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) / 2, OF_IMAGE_COLOR);
	this->frame = cv::Mat(this->frame_img.getHeight(), this->frame_img.getWidth(), CV_MAKETYPE(CV_8UC3, this->frame_img.getPixels().getNumChannels()), this->frame_img.getPixels().getData(), 0);
	
	this->eye_cascade.load("D:\\opencv-3.3.0\\build\\install\\etc\\haarcascades\\haarcascade_eye.xml");
	this->left_eye_cascade.load("D:\\opencv-3.3.0\\build\\install\\etc\\haarcascades\\haarcascade_lefteye_2splits.xml");
	this->right_eye_cascade.load("D:\\opencv-3.3.0\\build\\install\\etc\\haarcascades\\haarcascade_righteye_2splits.xml");

	int eye_size = 200;
	this->eye_img.allocate(eye_size, eye_size, OF_IMAGE_COLOR);
	unsigned char* pixels = this->eye_img.getPixels().getData();

	float r_power = 1.0;
	float g_power = 0.2;
	float b_power = 0.2;

	for (int x = 0; x < eye_size; x++) {
		for(int y = 0; y < eye_size; y++) {
			float distance = ((eye_size / 2 - x) * (eye_size / 2 - x) + (eye_size / 2 - y) * (eye_size / 2 - y)) / 50.f + 0.01;

			int r = (255 * r_power) / distance;
			if (r > 255) { r = 255; }

			int g = (255 * g_power) / distance;
			if (g > 255) { g = 255; }

			int b = (255 * b_power) / distance;
			if (b > 255) { b = 255; }

			pixels[x * 3 * eye_size + y * 3 + 0] = r;
			pixels[x * 3 * eye_size + y * 3 + 1] = g;
			pixels[x * 3 * eye_size + y * 3 + 2] = b;
		}
	}

	this->eye_img.update();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!this->cap.isOpened()) { return; }

	cv::Mat src;
	this->cap >> src;
	cv::resize(src, this->frame, cv::Size(), 0.5, 0.5);

	if (this->frame.empty()) { return; }

	cv::cvtColor(this->frame, this->frame, CV_RGB2BGR);
	cv::flip(this->frame, this->frame, 1);
	cv::cvtColor(this->frame, this->gray_frame, CV_RGB2GRAY);
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();

	ofTranslate(-this->frame_img.getWidth() / 2, -this->frame_img.getHeight() / 2);

	vector<cv::Rect> eyes;
	this->eye_cascade.detectMultiScale(this->frame, eyes);

	//vector<cv::Rect> left_eyes;
	//this->left_eye_cascade.detectMultiScale(this->gray_frame, left_eyes);	

	//vector<cv::Rect> right_eyes;
	//this->right_eye_cascade.detectMultiScale(this->gray_frame, right_eyes);

	ofSetColor(255);
	this->frame_img.update();
	this->frame_img.draw(0, 0);

	for (cv::Rect r : eyes) {
		//ofSetColor(255, 0, 0);
		//ofEllipse(ofVec3f(r.x + r.size().width / 2, this->frame_img.getHeight() - r.y - r.size().height / 2, 0), 15, 15);
		this->eye_img.draw(ofVec3f(r.x + r.size().width / 2 - 100, this->frame_img.getHeight() - r.y - r.size().height / 2 - 100, 0));
	}

	//for (cv::Rect r : left_eyes) {
	//	ofSetColor(255, 0, 0);
	//	ofRect(ofVec3f(r.x, this->frame_img.getHeight() - r.y, 0), r.size().width, -r.size().height);
	//}

	//for (cv::Rect r : right_eyes) {
	//	ofSetColor(0, 0, 255);
	//	ofRect(ofVec3f(r.x, this->frame_img.getHeight() - r.y, 0), r.size().width, -r.size().height);
	//}

	this->cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
