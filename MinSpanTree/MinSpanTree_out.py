import networkx as nx
import matplotlib.pyplot as plt
import sys
output_graph = True
add_weights = True
is_directed = False
if len(sys.argv) > 1 and int(sys.argv[1]) == 0:
	output_graph = False
if len(sys.argv) > 2 and int(sys.argv[2]) == 0:
	add_weights = False
if len(sys.argv) > 3 and int(sys.argv[3]) != 0:
	is_directed = True

with open('in.txt', 'r') as f:
	lines = f.read().split("\n")
	edges = [line.split(" ") for line in lines[1:] if line]

if add_weights:
	edges = [(int(c[0]), int(c[1]), int(c[2])) for c in edges]
else:
	edges = [(int(c[0]), int(c[1])) for c in edges]

if output_graph:
	with open('out.txt', 'r') as f:
		lines = f.read().split("\n")
		mst_edges = [line.split(" ") for line in lines[1:] if line]

	if add_weights:
		mst_edges = [(int(c[0]), int(c[1]), int(c[2])) for c in mst_edges]
	else:
		mst_edges = [(int(c[0]), int(c[1])) for c in mst_edges]

G = nx.DiGraph()
if add_weights:
	G.add_weighted_edges_from(edges)
else:
	G.add_edges_from(edges)

values = ['lime']*len(G.nodes())

pos = nx.circular_layout(G)
nx.draw_networkx_nodes(G, pos, node_color = values, node_size = 300)
nx.draw_networkx_labels(G, pos)

if add_weights:
	labels = nx.get_edge_attributes(G,'weight')
	nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
nx.draw_networkx_edges(G, pos, edgelist=edges, arrows=is_directed)
plt.savefig('mst_in.png', bbox_inches='tight')

if output_graph:
	nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='white', arrows=is_directed, width=1.3)
	nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='r', arrows=is_directed, width=2)
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
	nx.draw_networkx_edges(G, pos, edgelist=edges, arrows=is_directed)
	nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='white', arrows=is_directed, width=1.3)
	nx.draw_networkx_edges(G, pos, edgelist=mst1_edges, edge_color='r', arrows=is_directed, width=2)
	plt.savefig('mst1_out.png', bbox_inches='tight')
	plt.clf()
except Exception as e:
	pass