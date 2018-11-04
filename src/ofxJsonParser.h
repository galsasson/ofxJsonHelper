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
	static string parseString(const Json::Value& val, string def="");
	static bool parseBool(const Json::Value& val, bool def=false);
	static int parseInt(const Json::Value& val, int def=0);
	static float parseFloat(const Json::Value& val, float def=0);
	static double parseDouble(const Json::Value& val, double def=0);
	static ofColor parseColor(const Json::Value& val, const ofColor& def=ofColor(255));
	static ofColor parseColorInt(const Json::Value& val, const ofColor& def = ofColor(255));
	static ofVec4f parseVector(const Json::Value& val, const ofVec4f& def=ofVec4f());
	static ofRectangle parseRect(const Json::Value& val);
	static string toString(const ofColor& color);
	static void objectMerge(Json::Value& dst, const Json::Value& src);
	static void overrideOnlyMerge(Json::Value& dst, const Json::Value& src);
};
#endif /* ofxJsonParser_h */
