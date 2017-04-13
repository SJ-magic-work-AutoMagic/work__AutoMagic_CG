/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp()
: OscDj("127.0.0.1", 12357, 12358)
// , Osc_AcsMotion("127.0.0.1", 15001, 15000)
, Osc_AcsMotion("10.0.0.1", 15001, 15000)	// when not connected, app crashes.
												// 127.0.0.1 is OK.
, Cg(CG::getInstance())
, b_DispFrameRate(true)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
}

/******************************
******************************/
void ofApp::exit()
{
}


//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle( "CG" );
	ofSetWindowShape( WIDTH, HEIGHT );
	
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	mainOutputSyphonServer.setName("CG Screen Output");
	
	/********************
	********************/
	Cg->setup();
}

/******************************
******************************/
void ofApp::ChangeCgId_OscFrom_AcsMotion()
{
	while(Osc_AcsMotion.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc_AcsMotion.OscReceive.getNextMessage(&m_receive);
		
		if(m_receive.getAddress() == "/Motion"){
			int MotionId = m_receive.getArgAsInt32(0);
			
			int temp_i		= m_receive.getArgAsInt32(1);
			float temp_f	= m_receive.getArgAsFloat(2);
			temp_f			= m_receive.getArgAsFloat(3);
			
			Cg->ChangeId(MotionId);
		}
	}
}

/******************************
******************************/
void ofApp::Res_OscFrom_Dj()
{
	while( OscDj.OscReceive.hasWaitingMessages() ){
		ofxOscMessage m_receive;
		OscDj.OscReceive.getNextMessage(&m_receive);
		
		/********************
		********************/
		if(m_receive.getAddress() == "/AreYouReady"){
			m_receive.getArgAsInt32(0); // 読み捨て
			
			/* always yes. */
			ofxOscMessage m_send;
			m_send.setAddress("/Ready");
			m_send.addIntArg(1); // yes.
			OscDj.OscSend.sendMessage(m_send);
			
		}else if(m_receive.getAddress() == "/Quit"){
		
			// std::exit(1);
			ofExit();
			return;
			
		}else if(m_receive.getAddress() == "/VJColorTheme"){
			int ColorThemeID = m_receive.getArgAsInt32(0);
			
			ColorChange(COLORPATTERNS(ColorThemeID));
		}
	}
}

/******************************
******************************/
void ofApp::ColorChange(COLORPATTERNS id)
{
	Cg->set_color( id );
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	Res_OscFrom_Dj();
	ChangeCgId_OscFrom_AcsMotion();
	
	/********************
	********************/
	Cg->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0, 0, 0, 0);
	// ofBackground(0, 0, 0, 255);
	ofSetColor(255, 255, 255, 255);
	
	/********************
	********************/
	if(b_DispFrameRate){
		ofSetColor(255, 255, 255, 150);
		
		char buf[BUF_SIZE];
		sprintf(buf, "FrameRate = %5.1f", ofGetFrameRate());
		ofDrawBitmapString(buf, 10, 10);
	}
	
	/********************
	********************/
	Cg->draw(255);
	
	/********************
	********************/
	mainOutputSyphonServer.publishScreen();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	Cg->keyPressed(key);
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
