/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "payments/payments_main.h"

#include "payments/payments_common.h"
#include "boxes/language_box.h"
#include "boxes/confirm_box.h"
#include "boxes/about_box.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/wrap/slide_wrap.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/discrete_sliders.h"
#include "ui/widgets/buttons.h"
#include "info/profile/info_profile_cover.h"
#include "data/data_user.h"
#include "data/data_session.h"
#include "data/data_cloud_themes.h"
#include "data/data_chat_filters.h"
#include "lang/lang_keys.h"
#include "lang/lang_instance.h"
#include "storage/localstorage.h"
#include "main/main_session.h"
#include "main/main_session_settings.h"
#include "main/main_account.h"
#include "main/main_app_config.h"
#include "apiwrap.h"
#include "api/api_sensitive_content.h"
#include "api/api_global_privacy.h"
#include "window/window_session_controller.h"
#include "core/click_handler_types.h"
#include "base/call_delayed.h"
#include "facades.h"
#include "app.h"
#include "styles/style_settings.h"

namespace Payments {

void SetupSections(
		not_null<Window::SessionController*> controller,
		not_null<Ui::VerticalLayout*> container,
		Fn<void(Type)> showOther) {
}

Main::Main(
	QWidget *parent,
	not_null<Window::SessionController*> controller)
: Section(parent)
, _controller(controller) {
	setupContent(controller);
}

void Main::keyPressEvent(QKeyEvent *e) {
	return Section::keyPressEvent(e);
}

void Main::setupContent(not_null<Window::SessionController*> controller) {
	const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

	const auto cover = content->add(object_ptr<Info::Profile::Cover>(
		content,
		controller->session().user(),
		controller));
	cover->setOnlineCount(rpl::single(0));

	SetupSections(controller, content, [=](Type type) {
		_showOther.fire_copy(type);
	});
}

} // namespace Payments
