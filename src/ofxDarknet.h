#pragma once

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define GPU

#include "ofMain.h"

#include "activations.h"
#include "avgpool_layer.h"
#include "activation_layer.h"
#include "option_list.h"
#include "image.h"
#include "parser.h"
#include "list.h"
#include "box.h"
#include "tree.h"
#include "layer.h"
#include "matrix.h"
#include "connected_layer.h"
#include "gru_layer.h"
#include "rnn_layer.h"
#include "crnn_layer.h"
#include "detection_layer.h"
#include "region_layer.h"
#include "normalization_layer.h"
#include "reorg_layer.h"

#include "cost_layer.h"
#include "softmax_layer.h"
#include "route_layer.h"
#include "shortcut_layer.h"
#include "cuda.h"
#include "utils.h"
#include "nightmare.h"
#include "rnn.h"

#include "ofxOpenCv.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#endif

struct detected_object {
	ofRectangle rect;
	std::string label;
	float probability;
	ofColor color;
};

struct classification {
	std::string label;
	float probability;
};

class ofxDarknet
{
public:
	ofxDarknet();
	~ofxDarknet();

	void init( std::string cfgfile, std::string weightfile, std::string datacfg = "", std::string nameslist = "" );
	std::vector< detected_object > yolo( ofPixels & pix, float threshold = 0.24f );
	ofImage nightmate( ofPixels & pix, int max_layer, int range, int norm, int rounds, int iters, int octaves, float rate, float thresh );
	std::vector< classification > classify( ofPixels & pix, int count = 5 );
	std::string rnn( int num, std::string seed, float temp );

	void train_rnn( std::string textfile, std::string cfgfile );

private:
	list1 *options1;
	char **names;

	network net;

	image convert( ofPixels & pix );
	ofPixels convert( image & image );
};