#include<stdio.h>
#include<stdlib.h>
#include <string.h>


#define MAX_SIZE 10000
#define MAX_NODE_NUM 4000
#define MAX_EDGE_NUM 4000
#define INF 999999999

typedef struct Map {

	int nodeNum;
<<<<<<< HEAD
	//int edgeNum;
=======
<<<<<<< HEAD
	//int edgeNum;
=======
	int edgeNum;
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
	double adjMatrix[MAX_NODE_NUM][MAX_NODE_NUM];// 邻接矩阵
	int nodeId[MAX_NODE_NUM];//保存node的id
	double lat[MAX_NODE_NUM];
	double lon[MAX_NODE_NUM];
	int node1[MAX_EDGE_NUM]; //保存边的第一个端点的id
	int node2[MAX_EDGE_NUM]; //保存边的第二个端点的id
	double weights[MAX_EDGE_NUM]; // 保存每条边的权重

}Map;
Map mymap;
int prev[MAX_NODE_NUM], visited[MAX_NODE_NUM],path[MAX_NODE_NUM];
double dist[MAX_NODE_NUM];

// 初始化图，主要是将邻接矩阵中的元素变为INF
void init_mymap() {
	int i,j;
	for (i = 0; i < MAX_NODE_NUM; i++)
	{
		for (j = 0; j < MAX_NODE_NUM; j++)
			mymap.adjMatrix[i][j] = INF;
	}
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
// 生成整个地图的信息
void generate_gnuplot_data(const char *mapPath)
{
	int i;
	int node1, node2;
	char str[MAX_SIZE];

	FILE *fp0 = fopen(mapPath, "w");
	if (NULL == fp0)
	{
		printf("Failed to open the map file !\n");
		exit(0);
	}
	//printf("edgeNum:%d\n", mymap.edgeNum);
	for (i = 0; i < mymap.edgeNum; i++)
	{
		node1 = locateNode(mymap.node1[i]);
		node2 = locateNode(mymap.node2[i]);
		// printf("%d:(%f,%f)\n", i, mymap.lon[node1], mymap.lat[node1]);
		fprintf(fp0, "%f %f\n", mymap.lon[node1], mymap.lat[node1]);
		fprintf(fp0, "%f %f\n", mymap.lon[node2], mymap.lat[node2]);
		fprintf(fp0, "\n");
	}
	fclose(fp0);
}

>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
// 从.map文件中分离node 和 link 信息
int read(const char *mapPath,const char *nodePath, const char *linkPath)
{
	FILE *fp0,*fp1,*fp2;
	char str[MAX_SIZE];
	fp0 = fopen(mapPath, "r");
	if (NULL == fp0)
	{
		printf("Failed to open the map file !\n");
		exit(0);
	}
	fp1 = fopen(nodePath, "w");
	if (NULL == fp1)
	{
		printf("Failed to open the node file !\n");
		exit(0);
	}
	fp2 = fopen(linkPath, "w");
	if (NULL == fp2)
	{
		printf("Failed to open the link file !\n");
		exit(0);
	}
	while (fgets(str, MAX_SIZE, fp0) != NULL)
	{
		//fputs(str, stdout); //把字符串输出到屏幕
		if (str[1] == 'n')
		{
			fputs(str, fp1);
		}
		else if (str[1] == 'l')
		{
			fputs(str, fp2);
		}
		else {
			continue;
		}

	}
	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

//从给定的nodeId获取该点在邻接表中的下标
int locateNode(int nodeId)
{
	int i = 0;
	int find = 0;
	for (; i < mymap.nodeNum; i++)
	{
		if (mymap.nodeId[i] == nodeId){
			find = 1;
			break;
		}
	}
	if(1==find)
		return i;
	return -1;
}

//从两个TXT中读取node数据，和边的数据
int process_data(const char *nodePath, const char *linkPath)
{
	FILE *fp0, *fp1;
	char str[MAX_SIZE];
	double lat;
	double lon;
	int id;
	char temp[100] = { '\0' };
	int index;
	int i;
	int nodeNum = 0;
	int edgeNum = 0;
	int node1, node2,node1_index,node2_index;
	double length;
	fp0 = fopen(nodePath, "r");
	if (NULL == fp0)
	{
		printf("Failed to open the node file !\n");
		exit(0);
	}
	fp1 = fopen(linkPath, "r");
	if (NULL == fp1)
	{
		printf("Failed to open the link file !\n");
		exit(0);
	}

	// 初始化地图信息
	init_mymap();

	// 获取点的数据
	while (fgets(str, MAX_SIZE, fp0) != NULL)
	{
		//先得到id的数据
		for (i = 0; str[i] != 'i'; i++) {}
		index = i + 3;
		for (i = 0; str[i+index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		id = atoi(temp);

		//得到lat的数据
		index = index + i + 5;
		for (i = 0; str[i + index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		lat = atof(temp);
		//得到lon的数据
		index = index + i + 5;
		for (i = 0; str[i + index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		lon = atof(temp);
		//printf("id:%d , lat:%f ,lon:%f\n", id, lat, lon);

		mymap.nodeId[nodeNum] = id;
		mymap.lat[nodeNum] = lat;
		mymap.lon[nodeNum] = lon;
		nodeNum++;
	}
	mymap.nodeNum = nodeNum;

	// 获取边的数据
	while (fgets(str, MAX_SIZE, fp1) != NULL)
	{
		//先找到第一个node,先跳过link的‘n'
		for (i = 10; str[i] != 'n'; i++) {
			
		}
		index = i + 5;
		for (i = 0; str[i + index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		node1 = atoi(temp);

		//得到第二个node
		index = index + i + 6;

		for (i = 0; str[i + index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		node2 = atoi(temp);
		//得到length
		index = index + i ;	
		for (i = index; str[i] != 'l'; i++) {}
		index = i + 7;

		for (i = 0; str[i + index] != ' '; i++) {
			temp[i] = str[i + index];
		}
		temp[i] = '\0';
		length = atof(temp);
		// printf("node1:%d , node2:%d ,length:%f\n", node1, node2, length);
		node1_index = locateNode(node1);
		node2_index = locateNode(node2);
		if (-1 == node1_index || -1 == node2_index)
		{
			printf("The node doesn't exist on the map !\n");
			exit(0);
		}

		mymap.adjMatrix[node1_index][node2_index] = length;
		mymap.adjMatrix[node2_index][node1_index] = length;
		mymap.node1[edgeNum] = node1;
		mymap.node2[edgeNum] = node2;
		mymap.weights[edgeNum] = length;

		edgeNum++;
	}
<<<<<<< HEAD

	printf("nodeNum is %d\n", nodeNum);
	printf("edgeNum is %d\n", edgeNum);
=======
<<<<<<< HEAD

	printf("nodeNum is %d\n", nodeNum);
	printf("edgeNum is %d\n", edgeNum);
=======
	
	mymap.edgeNum = edgeNum;

	// printf("nodeNum is %d\n", nodeNum);
	// printf("edgeNum is %d\n", edgeNum);
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
	fclose(fp0);
	fclose(fp1);

}

<<<<<<< HEAD
// 迪杰斯特拉算法，输入的是两个点的id
int find(int start, int end)
=======
<<<<<<< HEAD
// 迪杰斯特拉算法，输入的是两个点的id
int find(int start, int end)
=======
// 迪杰斯特拉算法，输入的是两个点的id, 如果两个点可达，path是保存路径dat的路径
int find(int start, int end, const char *Path)
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
{
	
	int startIndex ,endIndex ;
	int i,j,k,t;
	double minDist,temp;
	int pathNode = 0;
<<<<<<< HEAD

=======
<<<<<<< HEAD

=======
	FILE *fp0;
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
	int id;
	double lat, lon;
	// 先将id转化为矩阵下标的形式
	endIndex = locateNode(end);
	startIndex = locateNode(start);
	if (-1 == startIndex || -1 == endIndex)
	{
		printf("The node doesn't exist on the map and cannot be calculated as a shortest path !\n");
		exit(0);
	}

	memset(visited, 0, sizeof(visited));
	memset(prev, 0, sizeof(prev)); 
	memset(path, 0, sizeof(path));
	// 初始化
	for (i = 0; i < mymap.nodeNum; i++)
	{
		visited[i] = 0;              // 顶点i的最短路径还没获取到
		dist[i] = mymap.adjMatrix[startIndex][i];// 保存最短路径
		if (mymap.adjMatrix[startIndex][i] != INF)
			prev[i] = startIndex;
		else
			prev[i] = -1;// 顶点i的前驱顶点为-1

	}
	// 对起点自身进行初始化
	visited[startIndex] = 1;
	dist[startIndex] = 0;

	// 每次找出一个顶点的最短路径。
	for (i = 1; i < mymap.nodeNum; i++)
	{
		// 寻找当前最小的路径；
		// 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
		minDist = INF;
		for (j = 0; j < mymap.nodeNum; j++)
		{
			if (visited[j] == 0 && dist[j] < minDist)
			{
				minDist = dist[j];
				k = j;
			}
		}
		
		visited[k] = 1;

		//更新最短路径
		for (j = 0; j < mymap.nodeNum; j++)
		{
		
			if (visited[j] == 0 && (dist[k] + mymap.adjMatrix[k][j] < dist[j]))
			{
				dist[j] = dist[k] + mymap.adjMatrix[k][j];
				prev[j] = k;
			}
		}
	}

	// 打印最短路径
	if (startIndex == endIndex)
	{
		printf("The start node is the same as the end node!\n");
	}

	else if (prev[endIndex] == -1)
	{
		printf("Not reachable between two nodes!\n");
	}
	else
	{
		t = endIndex;
		while (t!= startIndex)
		{
			path[pathNode] = t;
			t = prev[t];
			pathNode++;
		}
		path[pathNode] = startIndex;
		pathNode++;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

		fp0 = fopen(Path, "w");
		if (NULL == fp0)
		{
			printf("Failed to open the path file !\n");
			exit(0);
		}

>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
		printf("The length of the shortest path between two nodes is %f\n", dist[endIndex]);
		printf("The shortest path of two nodes is\n");
		for (i = 0; i < pathNode-1; i++) {
			id = mymap.nodeId[path[pathNode - 1 - i]];
			lat = mymap.lat[path[pathNode - 1 - i]];
			lon = mymap.lon[path[pathNode - 1 - i]];
			printf("%d(%f,%f)", id, lat, lon);
			printf("-->");
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

			// 保存到文件中
			fprintf(fp0, "%f %f\n", lon, lat);

>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
		}
		id = mymap.nodeId[path[0]];
		lat = mymap.lat[path[0]];
		lon = mymap.lon[path[0]];
<<<<<<< HEAD
		printf("%d(%f,%f)", id, lat, lon);
		printf("\n");
=======
<<<<<<< HEAD
		printf("%d(%f,%f)", id, lat, lon);
		printf("\n");
=======
		// 保存到文件中
		fprintf(fp0, "%f %f\n", lon, lat);
		
		printf("%d(%f,%f)", id, lat, lon);
		printf("\n");

		fclose(fp0);
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
	}
	return 0;
}

/*最大的id ：2137538435 */
long long find_maxID(const char *nodePath)
{
	long long res = 0;
	long long t = 0;
	FILE *fp0;
	char str[MAX_SIZE];
	char temp[13] = { '\0'};
	int i;
	fp0 = fopen(nodePath, "r");
	if (NULL == fp0)
	{
		printf("Failed to open the map file !\n");
		exit(0);
	}
	while (fgets(str, MAX_SIZE, fp0) != NULL)
	{
		//fputs(str, stdout); //把字符串输出到屏幕
		for (i =0;str[i+9]!=' ';i++)
		{
			temp[i] = str[i + 9];
		}
		temp[i] = '\0';
		t = atoll(temp);
		if (t > res) res = t;			
	}
	fclose(fp0);
	return res;

}

/*最小id: -2143395366 */
long long find_minID(const char *nodePath)
{
	long long res = 0;
	long long t = 0;
	FILE *fp0;
	char str[MAX_SIZE];
	char temp[13] = { '\0' };
	int i;
	fp0 = fopen(nodePath, "r");
	if (NULL == fp0)
	{
		printf("Failed to open the map file !\n");
		exit(0);
	}
	while (fgets(str, MAX_SIZE, fp0) != NULL)
	{
		//fputs(str, stdout); //把字符串输出到屏幕
		for (i = 0; str[i + 9] != ' '; i++)
		{
			temp[i] = str[i + 9];
		}
		temp[i] = '\0';
		t = atoll(temp);
		if (t < res) res = t;

	}
	fclose(fp0);
	return res;

}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======


>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
int main() {
	/*
	char mapPath[] = "./Final_Map.map";
	char nodePath[] = "./node.txt";
	char linkPath[] = "./link.txt";
	read(mapPath, nodePath, linkPath);
	
	char *str = "-222";
	long s = atol(str);
	printf("%ld", s);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 3ab1616 (final commit)
	*/
	//process_data("./node.txt", "./link.txt");

	process_data("./nn.txt", "./ll.txt");
	find(2, 18);

	return 0;
<<<<<<< HEAD
}
=======
}
=======
	
	//process_data("./node.txt", "./link.txt");

	
	process_data("./nn.txt", "./ll.txt");
	find(2, 18);
	*/
	int node1 = -8847;
	int node2 = -2538;
	printf("Build global variables : mymap............\n");
	process_data("./node.txt", "./link.txt");
	printf("Generate all the data (nodes and links) in the map and save it as: map.dat file................\n");
	generate_gnuplot_data("./map.dat");
	printf("Find the shortest path of node1: %d and node2: %d, if it exists, save it as: path.dat file................\n", node1, node2);
	find(node1, node2, "./path.dat");

	return 0;
}
>>>>>>> 0fe2df6 (final commit)
>>>>>>> 3ab1616 (final commit)
