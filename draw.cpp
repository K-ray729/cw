#include"draw.h"

unordered_map<long, mynode> nodes;

// 将node行和link行从map文件中提取出来
void divide_node_link(string mapPath, string nodePath, string linkPath)
{
	ifstream ifs(mapPath);
	if (!ifs) {
		cout << "The map file does not exist (or open failed)!" << endl;
		exit(1);
	}

	ofstream in_link(linkPath);
	if (!in_link) {
		cout << "link_path error!" << endl;
		exit(1);
	}
	ofstream in_node(nodePath);
	if (!in_node) {
		cout << "node_path error!" << endl;
		exit(1);
	}

	string str;

	while (getline(ifs, str))
	{

		//cout << str << endl;
		if (str[1] == 'n') //node信息
		{
			in_node << str << "\n";
		}
		else if (str[1] == 'l') //link 信息
		{
			in_link << str << "\n";
		}
		else
		{
			continue;
		}
	}
	in_node.close();//关闭文件
	in_link.close();//关闭文件
}

// 从node.txt中获取所以点的信息
void get_all_nodes(string nodePath)
{
	ifstream ifs(nodePath);
	if (!ifs) {
		cout << "The map file does not exist (or open failed)!" << endl;
		exit(1);
	}
	string str;

	while (getline(ifs, str))
	{
		string tmp = "";
		long id;
		double lat;
		double lon;
		// 提取每个node的id，lat，和lon
		string::size_type position = str.find("id=");//找到id的位置
		if (position != str.npos)
		{
			string::size_type i = position + 3;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			id = stol(tmp);
		}
		tmp.clear();
		position = str.find("lat=");//找到lat的位置
		if (position != str.npos)
		{
			string::size_type i = position + 4;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			lat = stof(tmp);
		}
		tmp.clear();
		position = str.find("lon=");//找到lon的位置
		if (position != str.npos)
		{
			string::size_type i = position + 4;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			lon = stof(tmp);
		}
		mynode node;
		node.id = id;
		node.lat = lat;
		node.lon = lon;
		nodes[id] = node;
	}

	cout << "nodes size: " << nodes.size() << endl;
}

// 生成gnuplot绘制的数据
void generate_gnuplot_dat(string linkPath, string outPath)
{
	// 确保边文件存在
	ifstream link_ifs(linkPath);
	if (!link_ifs) {
		cout << "The node file does not exist (or open failed)!" << endl;
		exit(1);
	}
	ofstream in(outPath);
	if (!in) {
		cout << "outPath error!" << endl;
		exit(1);
	}

	string str;
	while (getline(link_ifs, str)) {  // 获得每行数据

		string tmp = "";
		long id;
		// 提取每条边的端点
		string::size_type position = str.find("node=");//找到第一个端点的位置
		if (position != str.npos)
		{
			string::size_type i = position + 5;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			id = stol(tmp);
			// 写入文件，点的位置
			in << nodes[id].lon << ' '<< nodes[id].lat<<'\n';
			cout << "id:" << id << "(" << nodes[id].lon << "," << nodes[id].lat << ")" << endl;
		}
		tmp.clear();
		position = str.find("node=", position + 5 );//找到第二个端点的位置
		if (position != str.npos)
		{
			string::size_type i = position + 5;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			id = stol(tmp);
			// 写入文件，点的位置
			in << nodes[id].lon << ' ' << nodes[id].lat << '\n';
			cout << "id:" << id << "(" << nodes[id].lon << "," << nodes[id].lat << ")" << endl;
		}
		in << '\n';
		cout << endl;

	}
	in.close();//关闭文件
}