#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

class Graph_M {
private:
    unordered_map<string, unordered_map<string, int>> adjList;

public:
    void addVertex(const string& vertex) {
        adjList[vertex] = unordered_map<string, int>();
    }

    void addEdge(const string& source, const string& destination, int weight) {
        adjList[source][destination] = weight;
        adjList[destination][source] = weight;
    }

    void display_Stations() {
        cout << "List of all stations:" << endl;
        int i = 1;
        for (const auto& vertex : adjList) {
            cout << i << ". " << vertex.first << endl;
            i++;
        }
        cout << endl;
    }

    void display_Map() {
        cout << "Metro Map:" << endl;
        for (const auto& vertex : adjList) {
            cout << vertex.first << " -> ";
            for (const auto& neighbor : vertex.second) {
                cout << neighbor.first << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool containsVertex(const string& vertex) {
        return adjList.find(vertex) != adjList.end();
    }

    bool hasPath(const string& source, const string& destination, unordered_map<string, bool>& processed) {
        if (source == destination) {
            return true;
        }

        processed[source] = true;

        for (const auto& neighbor : adjList[source]) {
            if (!processed[neighbor.first] && hasPath(neighbor.first, destination, processed)) {
                return true;
            }
        }

        return false;
    }

    int dijkstra(const string& source, const string& destination, bool isTime) {
        unordered_map<string, int> distance;
        for (const auto& vertex : adjList) {
            distance[vertex.first] = INT_MAX;
        }
        distance[source] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            string curr = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjList[curr]) {
                string next = neighbor.first;
                int weight = neighbor.second;

                if (distance[curr] + weight < distance[next]) {
                    distance[next] = distance[curr] + weight;
                    pq.push({distance[next], next});
                }
            }
        }

        return distance[destination];
    }

    vector<string> get_Interchanges(int distance) {
        vector<string> interchanges;
        int numInterchanges = 0;
        for (const auto& vertex : adjList) {
            if (vertex.second.size() > 2) {
                numInterchanges++;
            }
        }
        interchanges.push_back(to_string(distance));
        interchanges.push_back(to_string(numInterchanges));
        for (const auto& vertex : adjList) {
            if (vertex.second.size() > 2) {
                interchanges.push_back(vertex.first);
            }
        }
        return interchanges;
    }
};

int main() {
    Graph_M g;

    g.addVertex("Noida Sector");
    g.addVertex("Botanical Garden");
    g.addVertex("Yamuna Bank");
    g.addVertex("Rajiv Chowk-1");
    g.addVertex("Vaishali");
    g.addVertex("Akshardham");
    g.addVertex("Preet Vihar");
    g.addVertex("Laxmi Nagar");
    g.addVertex("Yamuna Bank");
    g.addVertex("Chandni Chowk-2");
    g.addVertex("Rajiv Chowk-2");
    g.addVertex("New Delhi");
    g.addVertex("Dwarka");
    g.addVertex("Hauz Khas");
    g.addVertex("Central Secretariat");

    g.addEdge("Noida Sector", "Botanical Garden", 3);
    g.addEdge("Botanical Garden", "Yamuna Bank", 4);
    g.addEdge("Yamuna Bank", "Akshardham", 2);
    g.addEdge("Akshardham", "Preet Vihar", 3);
    g.addEdge("Preet Vihar", "Laxmi Nagar", 2);
    g.addEdge("Laxmi Nagar", "Yamuna Bank", 6);
    g.addEdge("Yamuna Bank", "Rajiv Chowk-1", 5);
    g.addEdge("Rajiv Chowk-1", "Vaishali", 4);
    g.addEdge("Rajiv Chowk-1", "Rajiv Chowk-2", 0);
    g.addEdge("Rajiv Chowk-2", "Chandni Chowk", 1);
    g.addEdge("Chandni Chowk", "New Delhi", 3);
    g.addEdge("New Delhi", "Central Secretariat", 6);
    g.addEdge("Rajiv Chowk-2", "Hauz Khas", 10);
    g.addEdge("Hauz Khas", "Central Secretariat", 4);
    g.addEdge("Hauz Khas", "Dwarka", 12);
    g.addEdge("Dwarka", "Rajiv Chowk-2", 10);

    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****" << endl;

    while (true) {
        cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout << "1. LIST ALL THE STATIONS IN THE MAP" << endl;
        cout << "2. SHOW THE METRO MAP" << endl;
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "5. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "6. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "7. EXIT THE MENU" << endl;
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7): ";
        int choice = -1;
        cin >> choice;
        cout << "\n***********************************************************\n";

        if (choice == 7) {
            break;
        }

        switch (choice) {
            case 1:
                g.display_Stations();
                break;

            case 2:
                g.display_Map();
                break;

            case 3:
                {
                    string source, destination;
                    cout << "Enter source station: ";
                    cin.ignore();
                    getline(cin, source);
                    cout << "Enter destination station: ";
                    getline(cin, destination);

                    if (g.containsVertex(source) && g.containsVertex(destination)) {
                        unordered_map<string, bool> processed;
                        if (g.hasPath(source, destination, processed)) {
                            int distance = g.dijkstra(source, destination, false);
                            cout << "\nShortest distance from " << source << " to " << destination << " is: " << distance << " km" << endl;
                        } else {
                            cout << "\nNo path exists between " << source << " and " << destination << endl;
                        }
                    } else {
                        cout << "\nInvalid source or destination station" << endl;
                    }
                }
                break;

            case 4:
                {
                    string source, destination;
                    cout << "Enter source station: ";
                    cin.ignore();
                    getline(cin, source);
                    cout << "Enter destination station: ";
                    getline(cin, destination);

                    if (g.containsVertex(source) && g.containsVertex(destination)) {
                        unordered_map<string, bool> processed;
                        if (g.hasPath(source, destination, processed)) {
                            int time = g.dijkstra(source, destination, true);
                            cout << "\nShortest time to reach from " << source << " to " << destination << " is: " << time << " minutes" << endl;
                        } else {
                            cout << "\nNo path exists between " << source << " and " << destination << endl;
                        }
                    } else {
                        cout << "\nInvalid source or destination station" << endl;
                    }
                }
                break;

            case 5:
                {
                    string source, destination;
                    cout << "Enter source station: ";
                    cin.ignore();
                    getline(cin, source);
                    cout << "Enter destination station: ";
                    getline(cin, destination);

                    if (g.containsVertex(source) && g.containsVertex(destination)) {
                        unordered_map<string, bool> processed;
                        if (g.hasPath(source, destination, processed)) {
                            int distance = g.dijkstra(source, destination, false);
                            cout << "\nShortest path (distance wise) from " << source << " to " << destination << " is: " << distance << " km" << endl;
                            vector<string> interchanges = g.get_Interchanges(distance);
                            cout << "Number of interchanges on the path: " << interchanges[1] << endl;
                            cout << "Interchange stations: ";
                            for (int i = 2; i < interchanges.size(); i++) {
                                cout << interchanges[i] << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "\nNo path exists between " << source << " and " << destination << endl;
                        }
                    } else {
                        cout << "\nInvalid source or destination station" << endl;
                    }
                }
                break;

            case 6:
                {
                    string source, destination;
                    cout << "Enter source station: ";
                    cin.ignore();
                    getline(cin, source);
                    cout << "Enter destination station: ";
                    getline(cin, destination);

                    if (g.containsVertex(source) && g.containsVertex(destination)) {
                        unordered_map<string, bool> processed;
                        if (g.hasPath(source, destination, processed)) {
                            int time = g.dijkstra(source, destination, true);
                            cout << "\nShortest path (time wise) from " << source << " to " << destination << " is: " << time << " minutes" << endl;
                            vector<string> interchanges = g.get_Interchanges(time);
                            cout << "Number of interchanges on the path: " << interchanges[1] << endl;
                            cout << "Interchange stations: ";
                            for (int i = 2; i < interchanges.size(); i++) {
                                cout << interchanges[i] << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "\nNo path exists between " << source << " and " << destination << endl;
                        }
                    } else {
                        cout << "\nInvalid source or destination station" << endl;
                    }
                }
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << "\n***********************************************************\n";
    }

    cout << "\nThank you for using the Metro App!" << endl;

    return 0;
}
