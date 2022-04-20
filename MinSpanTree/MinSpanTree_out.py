import networkx as nx
import matplotlib.pyplot as plt
import sys
output_graph = True
if len(sys.argv) > 1 and int(sys.argv[1]) == 0:
	output_graph = False

with open('in.txt', 'r') as f:
    lines = f.read().split("\n")
    edges = [line.split(" ") for line in lines[1:] if line]

edges = [(int(c[0]), int(c[1]), int(c[2])) for c in edges]

if output_graph:
	with open('out.txt', 'r') as f:
	    lines = f.read().split("\n")
	    mst_edges = [line.split(" ") for line in lines[1:] if line]

	mst_edges = [(int(c[0]), int(c[1]), int(c[2])) for c in mst_edges]

G = nx.DiGraph()
G.add_weighted_edges_from(edges)

values = ['lime']*len(G.nodes())

pos = nx.circular_layout(G)
nx.draw_networkx_nodes(G, pos, node_color = values, node_size = 300)
nx.draw_networkx_labels(G, pos)

labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
nx.draw_networkx_edges(G, pos, edgelist=edges, arrows=False)
plt.savefig('mst_in.png', bbox_inches='tight')

if output_graph:
	nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='white', arrows=False, width=1.3)
	nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='r', arrows=False, width=2)
	plt.savefig('mst_out.png', bbox_inches='tight')
plt.clf()


try:
    with open('out1.txt', 'r') as f:
        lines = f.read().split("\n")
        mst1_edges = [line.split(" ") for line in lines[1:] if line]

    mst1_edges = [(int(c[0]), int(c[1]), int(c[2])) for c in mst1_edges]
    nx.draw_networkx_nodes(G, pos, node_color = values, node_size = 300)
    nx.draw_networkx_labels(G, pos)
    nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
    nx.draw_networkx_edges(G, pos, edgelist=edges, arrows=False)
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='white', arrows=False, width=1.3)
    nx.draw_networkx_edges(G, pos, edgelist=mst1_edges, edge_color='r', arrows=False, width=2)
    plt.savefig('mst1_out.png', bbox_inches='tight')
    plt.clf()
except Exception as e:
    pass