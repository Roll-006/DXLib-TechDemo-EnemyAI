#include "mission_ui.hpp"

MissionUI::MissionUI(const std::string& json_name) :
	mission_ui_data		(MissionUIData()),
	m_screen			(nullptr),
	m_text_center_pos	(v2d::GetZeroV<Vector2D<int>>()),
	m_alpha_blend_num	(0),
	m_blend_wait_timer	(0.0f),
	m_is_active			(false),
	m_is_wait_blend		(true),
	m_is_fade_out		(false)
{
	nlohmann::json j_data;
	if (json_loader::Load("Data/JSON/text_data.json", j_data))
	{
		mission_ui_data = j_data.at("text_data").at(json_name.c_str()).get<MissionUIData>();

		mission_ui_data.text_data.font_handle	= FontHandler::GetInstance()->GetFontHandle(mission_ui_data.text_data.font_path);
		mission_ui_data.text_data.font_size		= { GetDrawStringWidthToHandle(mission_ui_data.text_data.text.c_str(), -1, mission_ui_data.text_data.font_handle), GetFontSizeToHandle(mission_ui_data.text_data.font_handle) };
		mission_ui_data.text_data.u_int_color	= type_converter::ConvertHEXToUINT(mission_ui_data.text_data.hex_color);

		m_screen = std::make_shared<ScreenCreator>(mission_ui_data.screen_size, Vector2D<int>(Window::kCenterPos.x, Window::kScreenSize.y * mission_ui_data.height_ratio));
		m_text_center_pos = m_screen->GetHalfScreenSize();
	}
}

MissionUI::~MissionUI()
{

}

void MissionUI::Init()
{
	m_alpha_blend_num	= 0;
	m_is_wait_blend		= true;
	m_is_fade_out		= false;
}

void MissionUI::LateUpdate()
{
	if (!m_is_active) { return; }

	CalcBlendWaitTime();
	CalcDrawTime();
	CalcAlphaBlendNum();
	CreateScreen();
}

void MissionUI::Draw() const
{
	if (!m_is_active) { return; }

	m_screen->Draw();
}

void MissionUI::CalcAlphaBlendNum()
{
	if (m_is_wait_blend) { return; }

	const auto delta_time = GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (!m_is_fade_out && m_alpha_blend_num < UCHAR_MAX)
	{
		math::Increase(m_alpha_blend_num, static_cast<int>(mission_ui_data.fade_in_speed  * delta_time), UCHAR_MAX, false);
	}
	else if (m_is_fade_out)
	{
		math::Decrease(m_alpha_blend_num, static_cast<int>(mission_ui_data.fade_out_speed * delta_time), 0);
		m_is_active = m_alpha_blend_num > 0;
	}

	m_screen->GetGraphicer()->SetBlendNum(m_alpha_blend_num);
}

void MissionUI::CalcBlendWaitTime()
{
	if (!m_is_wait_blend) { return; }

	m_blend_wait_timer += GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (m_blend_wait_timer > mission_ui_data.blend_wait_time)
	{
		m_is_wait_blend = false;
	}
}

void MissionUI::CalcDrawTime()
{
	// ブレンド率が最大になってから消え始めるまでの時間を計測
	if (m_alpha_blend_num < UCHAR_MAX) { return; }

	m_draw_timer += GameTimeManager::GetInstance()->GetDeltaTime(TimeScaleLayerKind::kUI);
	if (m_draw_timer > mission_ui_data.draw_time)
	{
		m_is_fade_out = true;
	}
}

void MissionUI::CreateScreen()
{
	if (m_is_wait_blend) { return; }

	m_screen->UseScreen();

	DrawStringToHandle(
		static_cast<int>((m_screen->GetScreenSize().x - mission_ui_data.text_data.font_size.x) * 0.5f),
		static_cast<int>((m_screen->GetScreenSize().y - mission_ui_data.text_data.font_size.y) * 0.5f),
		mission_ui_data.text_data.text.c_str(), mission_ui_data.text_data.u_int_color, mission_ui_data.text_data.font_handle);

	m_screen->UnuseScreen();
}
