#ifndef CONSTANTS
#define CONSTANTS

const float PI =  3.14159265;

//define a big bounding box (bb)
//used in getting halfplanes defined by two nodes
const float TOP_Y = 5000;
const float BOTTOM_Y = -5000;
const float LEFT_X = -5000;
const float RIGHT_X = 5000;


const static int WIDTH = 1200;
const static int HEIGHT = 800;
const static int MARGIN = 20;

const static int GRAPH_WIN_WIDTH = 1000;
const static int GRAPH_WIN_HEIGHT = 600;
const static int GRAPH_WIN_MARGIN = 20;

enum GRAPHS {MAX_RANGE, AVG_RANGE, TOTAL_SUM};

#endif // CONSTANTS

