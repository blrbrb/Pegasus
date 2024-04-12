#ifndef SceneGraph_h
#define SceneGraph_h
class SceneNode: public sf::Transformable, public sf::Drawable,
	private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
	public:
		SceneNode();
		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);
	private:
		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const;

};
#endif 
