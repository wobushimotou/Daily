int turn(int d, int cmd) {
    int ret = d;
    
    switch(d) {
    case 0:
        if(cmd == -1) ret = 1; else ret = 3; break;
    case 1:
        if(cmd == -1) ret = 2; else ret = 0; break;
    case 2:
        if(cmd == -1) ret = 3; else ret = 1; break;
    case 3:
        if(cmd == -1) ret = 0; else ret = 2; break;
    default:
        break;
    }
    
    return ret;
}
 
bool judge(int x, int y, int** o, int os){
    int i;
    int r = x + y * 30000;
    int left = 0, mid = os / 2, right = os;
    
    if(!os || r > o[os-1][0] || r < o[0][0])
        return true;
   
    if(r == o[mid][0])
        return false;
    
    while(left + 1 < right) {
        if(r > o[mid][0]) {
            left = mid;
            mid = (left + right) / 2;
        } else if (r < o[mid][0]){
            right = mid;
            mid = (left + right) / 2;
        } else {
            return false;
        }
    }
    
    return true;
}
 
 
int cmp(void *a, void *b) {
    return (*(int **)a)[0] - (*(int **)b)[0];
}
 
int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize){
    int x = 0, y = 0;
    int d = 0;
    int ret = 0;
    
    char b[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int i;
    
    for(i = 0; i < obstaclesSize; i++)
        obstacles[i][0] = obstacles[i][0] + obstacles[i][1] * 30000;
    
    qsort(obstacles, obstaclesSize, sizeof(int *), cmp);
    
    for(i = 0; i < commandsSize; i++) {
        switch(commands[i]) {
        case -1:
        case -2:
 
            d = turn(d, commands[i]);
            break;
        default:
            while(commands[i]--) {
                if (judge(x+b[d][0], y+b[d][1], obstacles,obstaclesSize)) {
                    x += b[d][0];
                    y += b[d][1];
                } else
                break;
            }
            break;
        }
       
        ret = ret < x * x + y * y ?  x * x + y * y : ret;
    }
    
    return ret;
}
