#include "purpose_ui.hpp"

PurposeUI::PurposeUI(const std::string& json_name) :
	purpose_ui_data(PurposeUIData()),
	m_screen(nullptr),
	m_text_center_pos(v2d::GetZeroV<Vector2D<int>>()),
	m_alpha_blend_num(0),
	m_blend_wait_timer(0.0f),
	m_is_active(false),
	m_is_wait_blend(true),
	m_is_fade_out(false)
{
	nlohmann::json j_data;
	if (json_loader::Load("Data/JSON/text_data.json", j_data))
	{
		purpose_ui_data = j_data.at("text_data").at(json_name.c_str()).get<PurposeUIData>();

		purpose_ui_data.text_data.font_handle = FontHandler::GetInstance()->GetFontHandle(purpose_ui_data.text_data.font_path);
		purpose_ui_data.text_data.font_size = { GetDrawStringWidthToHandle(purpose_ui_data.text_data.text.c_str(), -1, purpose_ui_data.text_data.font_handle), GetFontSizeToHandle(purpose_ui_data.text_data.font_handle) };
		purpose_ui_data.text_data.u_int_color = type_converter::ConvertHEXToUINT(purpose_ui_data.text_data.hex_color);

		m_screen = std::make_shared<ScreenCreator>(purpose_ui_data.screen_size, Vector2D<int>(Window::kCenterPos.x, Window::kScreenSize.y * purpose_ui_data.height_ratio));
		m_text_center_pos = m_screen->GetHalfScreenSize();
	}
}

PurposeUI::~PurposeUI()
{

}

void PurposeUI::Init()
{
	m_alpha_blend_num = 0;
	m_is_wait_blend = true;
	m_is_fade_out = false;
}

void PurposeUI::LateUpdate()
{
	if (!m_is_active) { return; }

	CalcBlendWaitTime();
	CalcDrawTime();
	CalcAlphaBlendNum();
	CreateScreen();
}

void PurposeUI::Draw() const
{
	if (!m_is_active) { return; }

	m_screen->Draw();
}

void PurposeUI::CalcAlphaBlendNum()
{
	if (m_is_wait_blend) { return; }

	const auto delta_time = GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (!m_is_fade_out && m_alpha_blend_num < UCHAR_MAX)
	{
		math::Increase(m_alpha_blend_num, static_cast<int>(purpose_ui_data.fade_in_speed * delta_time), UCHAR_MAX, false);
	}
	else if (m_is_fade_out)
	{
		math::Decrease(m_alpha_blend_num, static_cast<int>(purpose_ui_data.fade_out_speed * delta_time), 0);
		m_is_active = m_alpha_blend_num > 0;
	}

	m_screen->GetGraphicer()->SetBlendNum(m_alpha_blend_num);
}

void PurposeUI::CalcBlendWaitTime()
{
	if (!m_is_wait_blend) { return; }

	m_blend_wait_timer += GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (m_blend_wait_timer > purpose_ui_data.blend_wait_time)
	{
		m_is_wait_blend = false;
	}
}

void PurposeUI::CalcDrawTime()
{
	// ブレンド率が最大になってから消え始めるまでの時間を計測
	if (m_alpha_blend_num < UCHAR_MAX) { return; }

	m_draw_timer += GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (m_draw_timer > purpose_ui_data.draw_time)
	{
		m_is_fade_out = true;
	}
}

void PurposeUI::CreateScreen()
{
	if (m_is_wait_blend) { return; }

	m_screen->UseScreen();

	DrawStringToHandle(
		static_cast<int>((m_screen->GetScreenSize().x - purpose_ui_data.text_data.font_size.x) * 0.5f),
		static_cast<int>((m_screen->GetScreenSize().y - purpose_ui_data.text_data.font_size.y) * 0.5f),
		purpose_ui_data.text_data.text.c_str(), purpose_ui_data.text_data.u_int_color, purpose_ui_data.text_data.font_handle);

	m_screen->UnuseScreen();
}
