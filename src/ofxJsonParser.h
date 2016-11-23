//
//  ofxJsonParser.h
//  g3
//
//  Created by Gal Sasson on 8/16/16.
//
//

#ifndef ofxJsonParser_h
#define ofxJsonParser_h

#include "ofMain.h"
#include "ofxJSON.h"

class ofxJsonParser
{
public:

	static bool parseBool(const Json::Value& val, bool def=false);
	static float parseFloat(const Json::Value& val, float def=0);
	static ofColor parseColor(const Json::Value& val);
	static ofVec4f parseVector(const Json::Value& val, const ofVec4f& def=ofVec4f());
	static ofRectangle parseRect(const Json::Value& val);
	static string toString(const ofColor& color);
	static void objectMerge(Json::Value& dst, const Json::Value& src);
};
#endif /* ofxJsonParser_h */
