#pragma once
#include "../JSON/json_loader.hpp"
#include "../Data/purpose_ui_data.hpp"
#include "../GameTime/game_time_manager.hpp"
#include "../Calculation/math.hpp"

class PurposeUI final
{
public:
	PurposeUI(const std::string& json_name);
	~PurposeUI();

	void Init();
	void LateUpdate();
	void Draw() const;

	void Activate() { m_is_active = true; }

private:

private:
	PurposeUIData					purpose_ui_data;

	std::shared_ptr<ScreenCreator>	m_screen;
	Vector2D<int>					m_text_center_pos;
	int								m_alpha_blend_num;
	float							m_blend_wait_timer;
	float							m_draw_timer;
	bool							m_is_active;
	bool							m_is_wait_blend;
	bool							m_is_fade_out;

	friend void from_json(const nlohmann::json& j_data, PurposeUI& purpose_ui);
	friend void to_json  (nlohmann::json& j_data, const PurposeUI& purpose_ui);
};


#pragma region from / to JSON
inline void from_json(const nlohmann::json& j_data, PurposeUI& purpose_ui)
{
	j_data.at("purpose_ui_data").get_to(purpose_ui.purpose_ui_data);
}

inline void to_json(nlohmann::json& j_data, const PurposeUI& purpose_ui)
{
	j_data = nlohmann::json
	{
		{ "purpose_ui_data", purpose_ui.purpose_ui_data },
	};
}
#pragma endregion
