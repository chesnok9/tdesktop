/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"
#include "base/object_ptr.h"

namespace Main {
class Session;
} // namespace Main

namespace Ui {
class VerticalLayout;
class FlatLabel;
class SettingsButton;
} // namespace Ui

namespace Window {
class SessionController;
} // namespace Window

namespace style {
struct SettingsButton;
} // namespace style

namespace Payments {

enum class Type {
	Main,
	Method,
};

using Button = Ui::SettingsButton;

class Section : public Ui::RpWidget {
public:
	using RpWidget::RpWidget;

	virtual rpl::producer<Type> sectionShowOther() {
		return nullptr;
	}
	virtual rpl::producer<bool> sectionCanSaveChanges() {
		return rpl::single(false);
	}
	virtual void sectionSaveChanges(FnMut<void()> done) {
		done();
	}

};

object_ptr<Section> CreateSection(
	Type type,
	not_null<QWidget*> parent,
	not_null<Window::SessionController*> controller);

} // namespace Settings
