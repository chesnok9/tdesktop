/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "payments/payments_common.h"

namespace Window {
class SessionController;
} // namespace Window

namespace Ui {
class VerticalLayout;
} // namespace Ui

namespace Payments {

class Main : public Section {
public:
	Main(QWidget *parent, not_null<Window::SessionController*> controller);

protected:
	void keyPressEvent(QKeyEvent *e) override;

private:
	void setupContent(not_null<Window::SessionController*> controller);

	const not_null<Window::SessionController*> _controller;
	rpl::event_stream<Type> _showOther;

};

} // namespace Payments
