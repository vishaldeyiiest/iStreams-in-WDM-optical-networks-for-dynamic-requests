# Efficient-igStreams-in-WDM-optical-networks
- This is one of the research projects. It is an approach to share backup paths to increase utilization in optical networks
## Based on research papers on optical networks
- papers are in the folder paper

## works done
- Source folder contains the c/cpp files for path generation. 
- Paths folder contains the generated paths
- It also contains source files for finding optimal results
- /testing contains the request sets represented by (src, dest) pair
- /data contains the networks on which the algorithms and simulations are tested. It contain standard networks 
  in optical networking like ARPANET, NSFNET, USANET, NJLATA.
  
## Future work
- Papertitled "An Online Cost-Efficient Protection Scheme for Quick Recovery in All-Optical WDM Mesh Networks"
  on this work under peer review at Photonic Network Communications, Springer.

### Abstract of my paper
- Since a single fiber carries a huge amount of data in Optical WDM Networks; a fiber 
  cut even for a brief period is a very serious event. Designing schemes to prevent
  disruption of user traffic and recovery techniques from failures is thus an important
  area of research. Since a single fiber-cut is the most common type of fault, in this  
  paper we address the problem of protecting all-optical WDM mesh networks from
  single link failure. Our proposed online protection scheme is an improvement over an
  existing approach and is not only cost-efficient in terms of network resource
  consumption but can also provide quick recovery from a link failure. We first provide an
  Integer Linear Program for the problem, and then propose a heuristic solution iStreams
  that can provide near optimal solution in polynomial time. Performance comparisons
  show that our heuristic algorithm is definitely an improvement.
