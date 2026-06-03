#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct SitemapNode {
    string url;
    vector<SitemapNode> children;
    bool circularReference = false;
};

SitemapNode buildTree(
    int node,
    const vector<string>& vertices,
    const vector<vector<int>>& adjMatrix,
    unordered_set<int>& visited)
{
    SitemapNode current;
    current.url = vertices[node];

    if (visited.count(node)) {
        current.circularReference = true; // evita recursion en print
        return current;
    }

    visited.insert(node);

    for (int j = 0; j < vertices.size(); j++) {
        if (adjMatrix[node][j] == 1) { // existe una conexion
            current.children.push_back(
                buildTree(j, vertices, adjMatrix, visited)
                );
        }
    }

    return current;
}

void printJSON(const SitemapNode& node, int indent = 0)
{
    string pad(indent, ' ');

    cout << pad << "{\n";
    // "url": "site.com"
    cout << pad << "  \"url\": \"" << node.url << "\"";

    if (node.circularReference) {
        cout << ",\n";
        cout << pad << "  \"circularReference\": true\n";
        cout << pad << "}";
        return;
    }

    cout << ",\n";
    cout << pad << "  \"children\": [\n";

    for (int i = 0; i < node.children.size(); i++) {
        printJSON(node.children[i], indent + 4);

        if (i + 1 < node.children.size())
            cout << ",";

        cout << "\n";
    }

    cout << pad << "  ]\n";
    cout << pad << "}";
}

int main()
{
    vector<string> vertices = {
        "site.com/home",
        "site.com/about",
        "site.com/contact",
        "site.com/team"
    };

    vector<vector<int>> adjacencyMatrix = {
        {0,1,1,0}, // home
        {0,0,0,1}, // about
        {0,0,0,0}, // contact
        {1,0,0,0}  // team
    };

    int root = 0;

    unordered_set<int> visited;
    SitemapNode rootSiteMapNode =
        buildTree(root, vertices, adjacencyMatrix, visited);

    printJSON(rootSiteMapNode);
}
