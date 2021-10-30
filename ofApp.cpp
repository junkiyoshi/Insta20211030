#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofNoFill();
	ofSetColor(239, 19, 19);
	ofDrawRectangle(glm::vec2(), 685, 685);

	int small_radius = 40;
	int big_radius = 90;
	int center = (big_radius + small_radius) / 2;
	int gap = big_radius - small_radius;

	ofSetColor(239, 19, 19);
	for (int x = -220; x <= 220; x += 220) {

		for (int y = -220; y <= 220; y += 220) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int deg = 0; deg < 360; deg += 10) {

				ofNoFill();
				ofBeginShape();
				for (int radius = small_radius; radius <= big_radius; radius += 1) {

					auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
					auto noise_deg = ofMap(ofNoise(x, y, radius * 0.001 + ofGetFrameNum() * 0.01), 0, 1, -20, 20);
					auto param = ofMap(abs(center - radius), 0, gap * 0.5, 4, 0);
					auto draw_deg = deg + noise_deg * param;

					auto vertex = glm::vec2(radius * cos(draw_deg * DEG_TO_RAD), radius * sin(draw_deg * DEG_TO_RAD));
					ofVertex(vertex);
				}
				ofEndShape();

				ofFill();
				ofDrawCircle(glm::vec2(small_radius * cos(deg * DEG_TO_RAD), small_radius * sin(deg * DEG_TO_RAD)), 2);
				ofDrawCircle(glm::vec2(big_radius * cos(deg * DEG_TO_RAD), big_radius * sin(deg * DEG_TO_RAD)), 2);
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}