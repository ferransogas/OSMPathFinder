# OSMPathNavigator

## Project Overview

This project is part of a programming lab assignment for the 2023-2024 academic year. The goal is to read and process geographical data from OpenStreetMap (OSM) in XML format. The application will extract nodes (points) and ways (roads) from the data and display them on a graphical map. In the second part, the project will include a feature to calculate the shortest path between two points of interest using graph-based algorithms.

## Features

- **XML Parsing**: Read OSM XML files and extract nodes and roads (ways), storing them in efficient data structures.
- **Graphical Map Display**: Visualize points of interest (POIs) and roads on an interactive map interface.
- **Shortest Path Algorithm**: Find the shortest path between two POIs using a custom pathfinding algorithm.
- **Custom Data Structures**: Implement optimized data structures such as graphs and Ball Trees to handle map data.

## Project Breakdown

### Part 1: Data Parsing and Visualization (Grade: 9.20/10)
- **Node and Way Extraction**: Extract data from an OSM XML file and store information about nodes and roads.
- **POI Representation**: Create classes to represent different POIs, such as restaurants and shops.
- **Road Representation**: Design a method to display roads using their latitude and longitude coordinates.
- **Initial Visualization**: Show POIs and roads on a map interface, laying the groundwork for the pathfinding feature in part two.

### Part 2: Shortest Path Calculation (Grade: 10/10)
- **Graph Construction**: Build a graph where nodes are connected based on geographical proximity.
- **BallTree Implementation**: Use a Ball Tree structure to quickly find the nearest node to a POI.
- **Pathfinding Algorithm**: Implement a shortest path algorithm to find the best route between two POIs.
- **Optimization**: Use the Haversine distance formula to calculate accurate distances between nodes on the map.
