/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "info/info_content_widget.h"
#include "info/info_controller.h"

namespace Payments {
class Section;
} // namespace Payments

namespace Info {
namespace Payments {

using Type = Section::PaymentsType;

struct Tag;

class Memento final : public ContentMemento {
public:
	Memento(not_null<PaymentData*> self, Type type);

	object_ptr<ContentWidget> createWidget(
		QWidget *parent,
		not_null<Controller*> controller,
		const QRect &geometry) override;

	Section section() const override;

	Type type() const {
		return _type;
	}

	not_null<PaymentData*> self() const {
		return paymentsSelf();
	}

	~Memento();

private:
	Type _type = Type();

};

class Widget final : public ContentWidget {
public:
	Widget(
		QWidget *parent,
		not_null<Controller*> controller);
	~Widget();

	not_null<PaymentData*> self() const;

	bool showInternal(
		not_null<ContentMemento*> memento) override;

	void setInternalState(
		const QRect &geometry,
		not_null<Memento*> memento);

private:
	void saveState(not_null<Memento*> memento);
	void restoreState(not_null<Memento*> memento);

	std::shared_ptr<ContentMemento> doCreateMemento() override;

	not_null<PaymentData*> _self;
	Type _type = Type();

	not_null<::Payments::Section*> _inner;

};

} // namespace Payments
} // namespace Info
