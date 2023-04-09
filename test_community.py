import unittest
from age_community_detection import Graph

class TestCommunity(unittest.TestCase):
    def test_community(self):
        """Test community detection"""
        nodes = [0, 1, 2, 3, 4, 5]
        edges = [[0, 1], [0, 2], [1, 2], [2, 3], [3, 4], [3, 5], [4, 5]]
        g = Graph.Graph()
        g.createGraph(nodes, edges)
        res = g.get_community()
        self.assertEqual(res,[1,1,1,0,0,0])