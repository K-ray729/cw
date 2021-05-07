#include"draw.h"

unordered_map<long, mynode> nodes;

// ��node�к�link�д�map�ļ�����ȡ����
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
		if (str[1] == 'n') //node��Ϣ
		{
			in_node << str << "\n";
		}
		else if (str[1] == 'l') //link ��Ϣ
		{
			in_link << str << "\n";
		}
		else
		{
			continue;
		}
	}
	in_node.close();//�ر��ļ�
	in_link.close();//�ر��ļ�
}

// ��node.txt�л�ȡ���Ե����Ϣ
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
		// ��ȡÿ��node��id��lat����lon
		string::size_type position = str.find("id=");//�ҵ�id��λ��
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
		position = str.find("lat=");//�ҵ�lat��λ��
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
		position = str.find("lon=");//�ҵ�lon��λ��
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

// ����gnuplot���Ƶ�����
void generate_gnuplot_dat(string linkPath, string outPath)
{
	// ȷ�����ļ�����
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
	while (getline(link_ifs, str)) {  // ���ÿ������

		string tmp = "";
		long id;
		// ��ȡÿ���ߵĶ˵�
		string::size_type position = str.find("node=");//�ҵ���һ���˵��λ��
		if (position != str.npos)
		{
			string::size_type i = position + 5;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			id = stol(tmp);
			// д���ļ������λ��
			in << nodes[id].lon << ' '<< nodes[id].lat<<'\n';
			cout << "id:" << id << "(" << nodes[id].lon << "," << nodes[id].lat << ")" << endl;
		}
		tmp.clear();
		position = str.find("node=", position + 5 );//�ҵ��ڶ����˵��λ��
		if (position != str.npos)
		{
			string::size_type i = position + 5;
			for (; str[i] != ' '; i++)
			{
				tmp.append(1, str[i]);
			}
			id = stol(tmp);
			// д���ļ������λ��
			in << nodes[id].lon << ' ' << nodes[id].lat << '\n';
			cout << "id:" << id << "(" << nodes[id].lon << "," << nodes[id].lat << ")" << endl;
		}
		in << '\n';
		cout << endl;

	}
	in.close();//�ر��ļ�
}