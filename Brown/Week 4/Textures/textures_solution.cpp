#include "textures_common.h"

#include <stdexcept>

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`



////// Интерфейс фигуры
//class IShape {
//public:
//	virtual ~IShape() = default;
//
//	// Возвращает точную копию фигуры.
//	// Если фигура содержит текстуру, то созданная копия содержит ту же самую
//	// текстуру. Фигура и её копия совместно владеют этой текстурой.
//	virtual std::unique_ptr<IShape> Clone() const = 0;
//
//	virtual void SetPosition(Point) = 0;
//	virtual Point GetPosition() const = 0;
//
//	virtual void SetSize(Size) = 0;
//	virtual Size GetSize() const = 0;
//
//	virtual void SetTexture(std::shared_ptr<ITexture>) = 0;
//	virtual ITexture* GetTexture() const = 0;
//
//	// Рисует фигуру на указанном изображении
//	virtual void Draw(Image&) const = 0;
//};


class Figure : public IShape {
public:
	void SetPosition(Point p) override {
		position_ = p;
	}

	Point GetPosition() const override {
		return position_;
	}

	void SetSize(Size s) override {
		size_ = s;
	}

	Size GetSize() const override {
		return size_;
	}

	void SetTexture(shared_ptr<ITexture> t) override {
		texture_ = t;
	}

	ITexture* GetTexture() const override {
		return texture_.get();
	}

	void Draw(Image& img) const override {
		auto texture_image = texture_ ? texture_->GetImage() : Image(size_.height, std::string(size_.width, '.'));

		const int h = texture_image.size();
		const int w = texture_image[0].size();

		for (int i = position_.y; i < position_.y + size_.height; ++i) {
			for (int j = position_.x; j < position_.x + size_.width; ++j) {
				if (IsPointInImage({ j,i }, img)) {
					Point transformed_point = { j - position_.x, i - position_.y };
					if (IsPointInFigure(transformed_point)) {
						if (IsPointInImage(transformed_point, texture_image)) {
							img[i][j] = texture_image[transformed_point.y][transformed_point.x];
						}
						else {
							img[i][j] = '.';
						}
					}
				}
			}
		}
	}
private:
	Point position_;
	Size size_;
	shared_ptr<ITexture> texture_;

	bool IsPointInImage(Point p,const Image& img) const {
		return p.x < img[0].size() && p.y < img.size() && p.x >= 0 && p.y >= 0;
	}

	virtual bool IsPointInFigure(Point) const = 0;
};

class Rectangle : public Figure {
public:
	unique_ptr<IShape> Clone() const override {
		return std::make_unique<Rectangle>(*this);
	}
private:
	bool IsPointInFigure(Point p) const override {
		return true;
	}
};

class Ellipse : public Figure {
public:
	unique_ptr<IShape> Clone() const override {
		return std::make_unique<Ellipse>(*this);
	}
private:
	bool IsPointInFigure(Point p) const override {
		return IsPointInEllipse(p, GetSize());
	}
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	switch (shape_type) {
	case ShapeType::Rectangle:
		return std::make_unique<Rectangle>();
	case ShapeType::Ellipse:
		return std::make_unique<Ellipse>();
	default:
		throw std::runtime_error("This shape type isn't supported");
	}
}