
// initial amount for input data:
#define ALLOC 128 
// doubled when needed in load_data()

double lap;
int cp;

typedef struct {
    char *src; // filename for data read 文件路径
    int n; // number of data points 数据点的数量
    float m; // slope
    float b; // y-intercept
    int rsqr; // correlation numerator, cov^2 / variances
    int r; // correlation
} protocolIO;
void Euclidean_distance_computing(void* args); 
void load_dataInt(protocolIO *io, int** x, int** y, int party);
void load_dataU(protocolIO *io, float** x, float** y, int party);
void check_mem(float* x, float* y, int party);
