/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "payments/payments_common.h"

#include "payments/payments_main.h"
#include "core/application.h"
#include "ui/wrap/padding_wrap.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/box_content_divider.h"
#include "ui/widgets/buttons.h"
#include "boxes/abstract_box.h"
#include "window/themes/window_theme_editor_box.h"
#include "window/window_session_controller.h"
#include "window/window_controller.h"
#include "lang/lang_keys.h"
#include "mainwindow.h"
#include "main/main_session.h"
#include "main/main_domain.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"

namespace Payments {

object_ptr<Section> CreateSection(
		Type type,
		not_null<QWidget*> parent,
		not_null<Window::SessionController*> controller) {
        switch (type) {
            case Type::Main:
            case Type::Method:
                return object_ptr<Main>(parent, controller);
        }
        Unexpected("Payments section type in Widget::createInnerWidget.");
    } // namespace Payments
}