#pragma once

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
class SpatialTreeBase{
public:
    virtual void insert(Point new_point)=0;
    virtual std::shared_ptr<Node> search(Point target)=0;
    virtual std::vector<Point> range(Rectangle region)=0;
    virtual Point nearest_neighbor(Point reference)=0;

protected:
    std::shared_ptr<Node> root;
};

} //spatial
} //utec