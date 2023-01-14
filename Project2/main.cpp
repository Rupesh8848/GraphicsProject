#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include<math.h>
#include<list>
#include<map>
#include<set>
#include<queue>
#include<stack>
#define infinity INT_MAX;
using namespace std;
int node_counter = 0;
bool ifSource = false;

class node {
public:
	int x_cor, y_cor, index;
	float red = 1.0f, green = 1.0f, blue = 1.0f;
	bool source = false, blocked = false;
};
node node1;
node nodes[505];
node * source_node= NULL;
node *destination_node = NULL;
stack <int> previous_path;
list<int> colored_elements;

void clearColor(int node_index) {
	nodes[node_index].red = 1.0f;
	nodes[node_index].green = 1.0f;
	nodes[node_index].blue = 1.0f;
	glutPostRedisplay();
}
//draws nodes
void draw(node n) {
	glPointSize(20);
	glColor3f(n.red, n.green, n.blue);
	glBegin(GL_POINTS);
	glVertex2f(n.x_cor, n.y_cor);
	glEnd();
}

//handle resizing of windows
void changeSize(int w, int h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, 700, 700, 0);
	glMatrixMode(GL_MODELVIEW);
}

//display whole function
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 505; i++) {
		draw(nodes[i]);
	}
	draw(node1);
	glutSwapBuffers();
}



void drawPath(int node_index) {
	nodes[node_index].red = 0.0f;
	nodes[node_index].green = 0.0f;
	if (nodes[node_index].blue == 0.0f)
		nodes[node_index].blue = 1.0f;
	glutPostRedisplay();
}


//calculate distance between cursor and the nodes
int calc_dist(int x1, int y1, int x2, int y2) {
	return pow(pow((x2 - x1), 2) + (pow((y2 - y1), 2)), 0.5);
}

//init background color
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

//detect mouse movement and its cordinates
/*void mouse_handler(int a, int b) {

	node1.x_cor = a;
	node1.y_cor = b;

	for (int i = 0; i < 196; i++) {
		if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, a, b) < 15 && !(nodes[i].source)) {
			nodes[i].blue = 0.0;
			nodes[i].red = 0.0;
		}
		else {
			nodes[i].red = 1.0;
			nodes[i].blue = 1.0;
		}
	}
	glutPostRedisplay();
}*/


void keyBoardHandler(unsigned char key, int x, int y) {
	if ((key == 115 || key == 83) && !source_node) {
		for (int i = 0; i < 505; i++) {
			if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10) {
				nodes[i].blue = 0.0;
				nodes[i].red = 0.0;
				source_node = &nodes[i];
			}
		}
	}
	else if ((key == 115 || key == 83) && source_node) {
		source_node->red = 1.0;
		source_node->blue = 1.0;
		for (int i = 0; i <= 505; i++) {
			if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10) {
				nodes[i].blue = 0.0;
				nodes[i].red = 0.0;
				source_node = &nodes[i];
			}
		}
	}

	if ((key == 100 || key == 68) && !destination_node) {
		for (int i = 0; i < 505; i++) {
			if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10) {
				nodes[i].blue = 0.0;
				nodes[i].green = 0.0;
				destination_node = &nodes[i];
			}
		}
	}
	else if ((key == 100 || key == 68) && destination_node) {
		destination_node->green = 1.0;
		destination_node->blue = 1.0;
		for (int i = 0; i < 505; i++) {
			if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10) {
				nodes[i].blue = 0.0;
				nodes[i].green = 0.0;
				destination_node = &nodes[i];
			}
		}
	}

	glutPostRedisplay();
}

void colorVisitedNode(int node_index) {
	//rgb(0.40,0.70,1.00)
	colored_elements.push_back(node_index);
	nodes[node_index].red = 0.40;
	nodes[node_index].green = 0.70;
	nodes[node_index].blue = 1.00;
	glutPostRedisplay();
	
}
//class graph {
//	map<int, list<int>> m; //first int is the node number and the second index is the surrounding node
//public:
//	void addEdge(int n, int neighbour) {
//		m[n].push_back(neighbour);
//		m[neighbour].push_back(n);
//	}
//	/*void printEdges() {
//		if (m.empty()) {
//			cout << "No nodes to print.";
//		}
//		for (auto element : m) {
//			cout << "node" << element.first << "->";
//			for (auto neighbours : element.second) {
//				cout << neighbours<<" ";
//			}
//			cout << '\n';
//		}
//	}*/
//
//	void swap_bool(map<int, list<bool>>& visited, int index) {
//		visited[index].pop_back();
//		visited[index].push_back(true);
//	}
//
//	bool is_neighbour(int current_node, int check_node) {
//		bool status;
//		for (auto element : m[current_node]) {
//			return element;
//		}
//	}
//
//	bool is_visited(map<int, list<bool>>& visited, int index) {
//		bool status;
//		for (auto element : visited[index]) {
//			if (element == false) {
//				return false;
//			}
//			else
//				return true;
//		}
//	}
//
//	int check_distance(map<int, list<int>>& distance, int index) {
//		for (auto element : distance[index]) {
//			return element;
//		}
//	}
//
//	int change_distance(map<int, list<int>>& distance, int index, int value) {
//		for (auto element : distance[index]) {
//			element = value;
//		}
//	}
//
//	int selectMinVertex(map<int, list<int>>& distance, map<int, list<bool>>& visited) {
//		int minimum = INT_MAX;
//		int vertex;
//		for (int i = 0; i < 505; i++) {
//			if (check_distance(distance, i) < minimum && is_visited(visited, i) == false) {
//				minimum = check_distance(distance, i);
//				vertex = i;
//			}
//		}
//		return vertex;
//
//	}
//
//	int check_parent_index(map<int, list<int>>& parent,int index) {
//		for (auto element : parent[index]) {
//			return element;
//		}
//	}
//
//	/*void change_color(map<int, list<int>>& parent) {
//		stack<int> s;
//		bool break_loop = false;
//		int node_value_checker = check_parent_index(destination_node->index);
//		while (!break_loop) {
//			for (int i = 0; i < 505; i++) {
//				if (-1 == node_value_checker) {
//					break_loop = true;
//					break;
//				}
//
//					
//
//			}
//		}
//
//	
//	}*/


//	void dijskstras() {
//		map<int, list<bool>> visited;
//		map<int, list<int>> distance;
//		map<int, list<int>> parent;
//		for (auto j : m) {
//			visited[j.first].push_back(false);
//			distance[j.first].push_back(INT_MAX);
//			parent[j.first].push_back(-1);
//		}
//		swap_bool(visited, source_node->index);
//		distance[source_node->index].pop_back();
//		distance[source_node->index].push_back(0);
//
//		for (int i = 0; i < 504; i++) {
//			int U = selectMinVertex(distance, visited);
//			swap_bool(visited, U);
//			for (int j = 0; j < 505; j++) {
//				if (is_neighbour(U, j) && is_visited(visited, U) == false && check_distance(distance, U) != INT_MAX && check_distance(distance, U) + 1 < check_distance(distance, j)) {
//					change_distance(distance, j, check_distance(distance, U) + 1);
//				}
//			}
//		}
//
//	}
//};

void resetNodesToWhite() {
	for (auto elements : colored_elements) {
		if (!nodes[elements].blocked) {
			nodes[elements].red = 1.0f;
			nodes[elements].green = 1.0f;
			nodes[elements].blue = 1.0f;
		}
		//draw(nodes[elements]);
	}
	glutPostRedisplay();
}
class breadth_first_search {
	map<int, list<int>> m;
	stack <int> path;
	
public:
	void addEdge(int n, int neighbour) { //makes the nodes list and then the neighbour list as:
				m[n].push_back(neighbour);  // 1 -> 0,23
				m[neighbour].push_back(n); //2->1,3,24 likewise
		}

	void bfs(int s , int e ) {
		resetNodesToWhite();
		queue <int> q;
		bool visited[505];
		int parent[505];
		bool visited_status = false;
		for (int i = 0; i < 505; i++) {
			visited[i] = false;
			parent[i] = NULL;
		}
		q.push(s);
		visited[s] = true;
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			for (auto element : m[node]) {
				if (!visited[element] && nodes[element].blocked != true) {
					q.push(element);
					visited[element] = true;
					parent[element] = node;
					if (visited_status == false)
					{
						colorVisitedNode(element);
					}
					if (element == destination_node->index)
						visited_status = true;
				}
			}
		}
		
		for (int at = e; at != NULL; at = parent[at]) {
			path.push(at);
		}
		
		if (path.empty()) {
			cout << "Sorry, all the paths are blocked and can't be accessed.";
		}
		while (!path.empty()) {
			/*cout << path.top() << " << ";*/
			/*cout << "Coloring new Path" << endl;*/
			drawPath(path.top());
			//previous_path.push(path.top());
			path.pop();
		}
		
		//resteing visited node to false
		visited_status = false;
		cout << endl;
	}


};


breadth_first_search g;

void handleRightClick(int option) {
	switch (option) {
	case 0:
		g.bfs(source_node->index, destination_node->index);
		break;

	default:
		break;
	}
		
			
}


//handle left click
void handleLeftClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 505; i++) {
			if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10 && nodes[i].blocked == false) {
				nodes[i].blue = 0.28;
				nodes[i].red = 0.29;
				nodes[i].green = 0.28;
				nodes[i].blocked = true;
			}
			else if (calc_dist(nodes[i].x_cor, nodes[i].y_cor, x, y) < 10 && nodes[i].blocked == true) {
				nodes[i].blue = 1.00;
				nodes[i].red = 1.00;
				nodes[i].green = 1.00;
				nodes[i].blocked = false;
			}
		}
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {

	for (int i = 35; i < 700; i += 30) { //top left = 0  top right = 22
		for (int j = 20; j < 700; j += 30) {
			nodes[node_counter].x_cor = j;
			nodes[node_counter].y_cor = i;
			nodes[node_counter].index = node_counter;
			node_counter++;
		}
	}
	
	
	for (int i = 0; i < 505; i ++) {
		for (int j = i; j < 505; j ++) {
			int dist = calc_dist(nodes[i].x_cor, nodes[i].y_cor, nodes[j].x_cor, nodes[j].y_cor);
			if (dist <= 35 && dist != 0) {
				g.addEdge(nodes[i].index, nodes[j].index);
			}
		}
	}

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	init();

	//for displaying 
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);

	//for handling key presses
	glutKeyboardFunc(keyBoardHandler);
	
	//handle left clicks
	glutMouseFunc(handleLeftClick);

	//handle right clicks
	int menu = glutCreateMenu(handleRightClick);
	glutAddMenuEntry("Breadth First Search", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//handle mouse event
	//glutPassiveMotionFunc(mouse_handler);
	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}