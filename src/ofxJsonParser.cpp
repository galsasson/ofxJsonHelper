//
//  ofxJsonParser.cpp
//  g3
//
//  Created by Gal Sasson on 8/16/16.
//
//

#include "ofxJsonParser.h"

string ofxJsonParser::parseString(const Json::Value& val, string def)
{
	if (val == Json::nullValue || !val.isString()) {
		return def;
	}
	return val.asString();
}

bool ofxJsonParser::parseBool(const Json::Value& val, bool def)
{
	if (val == Json::nullValue || !val.isBool()) {
		return def;
	}
	return val.asBool();
}

int ofxJsonParser::parseInt(const Json::Value& val, int def)
{
	if (val == Json::nullValue || !val.isInt()) {
		return def;
	}
	return val.asInt();
}

float ofxJsonParser::parseFloat(const Json::Value& val, float def)
{
	if (val == Json::nullValue || !val.isDouble()) {
		return def;
	}
	return val.asFloat();
}

double ofxJsonParser::parseDouble(const Json::Value& val, double def)
{
	if (val == Json::nullValue || !val.isDouble()) {
		return def;
	}
	return val.asDouble();
}

ofColor ofxJsonParser::parseColor(const Json::Value& val, const ofColor& def)
{
	if (val.isArray()) {
		if (val.size() == 1) {
			return ofFloatColor(val[0].asFloat(), val[0].asFloat(), val[0].asFloat(), 1);
		}
		float alpha = val.size()==4?val[3].asFloat():1;
		return ofFloatColor(val[0].asFloat(), val[1].asFloat(), val[2].asFloat(), alpha);
	}
	else if (val.isObject()) {
		if (!val.isMember("r") || !val.isMember("g") || !val.isMember("b")) {
			ofLogWarning("ofxJsonParser") << "cannot parse color: "<<val.toStyledString();
			return def;
		}
		else {
			float alpha = val.isMember("a")?val["a"].asInt():255;
			return ofColor(val["r"].asInt(), val["g"].asInt(), val["b"].asInt(), alpha);
		}
	}
	else if (val.isString()) {
		string colStr = val.asString();
		vector<string> parts = ofSplitString(colStr, " ");
		if (parts.empty()) {
			ofLogWarning("ofxJsonParser") << "Failed to parse color string (format: #RRGGBB A%). Got: '"<<colStr<<"'";
			return def;
		}
		int val = parts[0][0]=='#'?ofHexToInt(parts[0].substr(1, parts[0].size()-1)):ofHexToInt(parts[0]);
		float alpha = parts.size()==2?parts[1][parts[1].size()-1]=='%'?ofToFloat(parts[1].substr(0, parts[1].size()-1)):ofToFloat(parts[1]):100;
		return ofColor::fromHex(val, alpha*2.55);
	}
	else {
		ofLogWarning("JsonParser") << "cannot parse color: "<<val.toStyledString();
		return def;
	}
}

ofVec4f ofxJsonParser::parseVector(const Json::Value &val, const ofVec4f& def)
{
	if (val == Json::nullValue) {
		return def;
	}
	
	if (val.isArray()) {
		if (val.size()>=2 && val.size()<=4) {
			float z = val.size()>=3?val[2].asFloat():0;
			float w = val.size()==4?val[3].asFloat():0;
			return ofVec4f(val[0].asFloat(), val[1].asFloat(), z, w);
		}
		else {
			ofLogWarning("JsonParser") << "cannot parse vector: "<<val.toStyledString();
			return def;
		}
	}
	else if (val.isObject()) {
		if (val.size()>=2 && val.size()<=4) {
			float z = val.isMember("z")?val["z"].asFloat():0;
			float w = val.isMember("w")?val["w"].asFloat():0;
			return ofVec4f(val["x"].asFloat(), val["y"].asFloat(), z, w);
		}
		else {
			ofLogWarning("JsonParser") << "cannot parse vector: "<<val.toStyledString();
			return def;
		}
	}
	else {
		ofLogWarning("JsonParser") << "cannot parse vector: "<<val.toStyledString();
		return def;
	}
}

ofRectangle ofxJsonParser::parseRect(const Json::Value& val)
{
	if (val.isArray()) {
		if (val.size() == 4) {
			return ofRectangle(val[0].asFloat(), val[1].asFloat(), val[2].asFloat(), val[3].asFloat());
		}
		else {
			ofLogWarning("JsonParser") << "cannot parse rect: "<<val.toStyledString();
			return ofRectangle();
		}
	}
	else {
		ofLogWarning("JsonParser") << "cannot parse rect: "<<val.toStyledString();
		return ofRectangle();
	}
}

string ofxJsonParser::toString(const ofColor& color)
{
	char buff[256];
	sprintf(buff, "#%x %d%%", color.getHex(), int(float(color.a)/255*100));
	return buff;
}

void ofxJsonParser::objectMerge(Json::Value& dst, const Json::Value& src)
{
	if (!dst.isObject() || !src.isObject()) {
		return;
	}

	for (const string& key: dst.getMemberNames()) {
		if (src.isMember(key)) {
			if (dst[key].isObject() && src[key].isObject()) {
				objectMerge(dst[key], src[key]);
			}
			else {
				dst[key] = src[key];
			}
		}
	}
}
