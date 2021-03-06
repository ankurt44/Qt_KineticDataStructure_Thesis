#ifndef CONSTANTS
#define CONSTANTS

#include <QMetaType>

const float PI =  3.14159265;

//define a big bounding box (bb)
//used in getting halfplanes defined by two nodes
const float TOP_Y = 5000;
const float BOTTOM_Y = -5000;
const float LEFT_X = -5000;
const float RIGHT_X = 5000;


const static int WIDTH = 1350;
const static int HEIGHT = 800;
const static int MARGIN = 20;

const static int GRAPH_WIN_WIDTH = 1250;
const static int GRAPH_WIN_HEIGHT = 820;
const static int GRAPH_WIN_MARGIN = 20;

const static int GRAPH_WIDTH = 600;
const static int GRAPH_HEIGHT = 350;

enum GRAPHS {MAX_RANGE, AVG_RANGE, TOTAL_SUM_RANGE, MEDIAN_RANGE};
Q_DECLARE_METATYPE(GRAPHS);

//used to consider an precision error when calculating cross product
const static float EPSILON_CROSS_PRODUCT_ERROR = 0.005;

#endif // CONSTANTS

