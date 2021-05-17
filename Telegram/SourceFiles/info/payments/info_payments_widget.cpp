/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "info/payments/info_payments_widget.h"

#include "info/info_memento.h"
#include "info/info_controller.h"
#include "payments/payments_common.h"
#include "ui/ui_utility.h"

namespace Info {
namespace Payments {

Memento::Memento(not_null<PaymentData*> self, Type type)
: ContentMemento(Tag{ self })
, _type(type) {
}

Section Memento::section() const {
	return Section(_type);
}

object_ptr<ContentWidget> Memento::createWidget(
		QWidget *parent,
		not_null<Controller*> controller,
		const QRect &geometry) {
	auto result = object_ptr<Widget>(
		parent,
		controller);
	result->setInternalState(geometry, this);
	return result;
}

Memento::~Memento() = default;

Widget::Widget(
	QWidget *parent,
	not_null<Controller*> controller)
: ContentWidget(parent, controller)
, _self(controller->key().paymentsSelf())
, _type(controller->section().paymentsType())
, _inner(setInnerWidget(
	::Payments::CreateSection(
		_type,
		this,
		controller->parentController()))) {
	_inner->sectionShowOther(
	) | rpl::start_with_next([=](Type type) {
		controller->showPayments(type);
	}, _inner->lifetime());

	controller->setCanSaveChanges(_inner->sectionCanSaveChanges());
}

Widget::~Widget() = default;

not_null<PaymentData*> Widget::self() const {
	return _self;
}

bool Widget::showInternal(not_null<ContentMemento*> memento) {
	//if (const auto myMemento = dynamic_cast<Memento*>(memento.get())) {
	//	Assert(myMemento->self() == self());

	//	if (_inner->showInternal(myMemento)) {
	//		return true;
	//	}
	//}
	return false;
}

void Widget::setInternalState(
		const QRect &geometry,
		not_null<Memento*> memento) {
	setGeometry(geometry);
	Ui::SendPendingMoveResizeEvents(this);
	restoreState(memento);
}


std::shared_ptr<ContentMemento> Widget::doCreateMemento() {
	auto result = std::make_shared<Memento>(self(), _type);
	saveState(result.get());
	return result;
}

void Widget::saveState(not_null<Memento*> memento) {
	memento->setScrollTop(scrollTopSave());
}

void Widget::restoreState(not_null<Memento*> memento) {
	const auto scrollTop = memento->scrollTop();
	scrollTopRestore(memento->scrollTop());
}

} // namespace Payments
} // namespace Info
