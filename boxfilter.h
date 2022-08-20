#include <imgui.h>
#include <imgui_internal.h>
#include <ios>
#include <stdlib.h>
#include <ctype.h>
#include <cstdint>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

namespace ImGui
{
    // https://github.com/forrestthewoods/lib_fts
	
	ImVec2 operator+(const ImVec2& v1, const ImVec2& v2) {return ImVec2(v1.x + v2.x, v1.y + v2.y);}

    // Forward declarations for "private" implementation
    namespace fuzzy_internal {
        static bool fuzzy_match_recursive(const char* pattern, const char* str, int& outScore, const char* strBegin,
            uint8_t const* srcMatches, uint8_t* newMatches, int maxMatches, int nextMatch,
            int& recursionCount, int recursionLimit);
    }
    // Private implementation
    static bool fuzzy_internal::fuzzy_match_recursive(const char* pattern, const char* str, int& outScore,
        const char* strBegin, uint8_t const* srcMatches, uint8_t* matches, int maxMatches,
        int nextMatch, int& recursionCount, int recursionLimit)
    {
        // Count recursions
        ++recursionCount;
        if (recursionCount >= recursionLimit)
            return false;

        // Detect end of strings
        if (*pattern == '\0' || *str == '\0')
            return false;

        // Recursion params
        bool recursiveMatch = false;
        uint8_t bestRecursiveMatches[256];
        int bestRecursiveScore = 0;

        // Loop through pattern and str looking for a match
        bool first_match = true;
        while (*pattern != '\0' && *str != '\0') {

            // Found match
            if (tolower(*pattern) == tolower(*str)) {

                // Supplied matches buffer was too short
                if (nextMatch >= maxMatches)
                    return false;

                // "Copy-on-Write" srcMatches into matches
                if (first_match && srcMatches) {
                    memcpy(matches, srcMatches, nextMatch);
                    first_match = false;
                }

                // Recursive call that "skips" this match
                uint8_t recursiveMatches[256];
                int recursiveScore;
                if (fuzzy_match_recursive(pattern, str + 1, recursiveScore, strBegin, matches, recursiveMatches, sizeof(recursiveMatches), nextMatch, recursionCount, recursionLimit)) {

                    // Pick best recursive score
                    if (!recursiveMatch || recursiveScore > bestRecursiveScore) {
                        memcpy(bestRecursiveMatches, recursiveMatches, 256);
                        bestRecursiveScore = recursiveScore;
                    }
                    recursiveMatch = true;
                }

                // Advance
                matches[nextMatch++] = (uint8_t)(str - strBegin);
                ++pattern;
            }
            ++str;
        }

        // Determine if full pattern was matched
        bool matched = *pattern == '\0' ? true : false;

        // Calculate score
        if (matched) {
            const int sequential_bonus = 15;            // bonus for adjacent matches
            const int separator_bonus = 30;             // bonus if match occurs after a separator
            const int camel_bonus = 30;                 // bonus if match is uppercase and prev is lower
            const int first_letter_bonus = 15;          // bonus if the first letter is matched

            const int leading_letter_penalty = -5;      // penalty applied for every letter in str before the first match
            const int max_leading_letter_penalty = -15; // maximum penalty for leading letters
            const int unmatched_letter_penalty = -1;    // penalty for every letter that doesn't matter

            // Iterate str to end
            while (*str != '\0')
                ++str;

            // Initialize score
            outScore = 100;

            // Apply leading letter penalty
            int penalty = leading_letter_penalty * matches[0];
            if (penalty < max_leading_letter_penalty)
                penalty = max_leading_letter_penalty;
            outScore += penalty;

            // Apply unmatched penalty
            int unmatched = (int)(str - strBegin) - nextMatch;
            outScore += unmatched_letter_penalty * unmatched;

            // Apply ordering bonuses
            for (int i = 0; i < nextMatch; ++i) {
                uint8_t currIdx = matches[i];

                if (i > 0) {
                    uint8_t prevIdx = matches[i - 1];

                    // Sequential
                    if (currIdx == (prevIdx + 1))
                        outScore += sequential_bonus;
                }

                // Check for bonuses based on neighbor character value
                if (currIdx > 0) {
                    // Camel case
                    char neighbor = strBegin[currIdx - 1];
                    char curr = strBegin[currIdx];
                    if (::islower(neighbor) && ::isupper(curr))
                        outScore += camel_bonus;

                    // Separator
                    bool neighborSeparator = neighbor == '_' || neighbor == ' ';
                    if (neighborSeparator)
                        outScore += separator_bonus;
                }
                else {
                    // First letter
                    outScore += first_letter_bonus;
                }
            }
        }

        // Return best result
        if (recursiveMatch && (!matched || bestRecursiveScore > outScore)) {
            // Recursive score is better than "this"
            memcpy(matches, bestRecursiveMatches, maxMatches);
            outScore = bestRecursiveScore;
            return true;
        }
        else if (matched) {
            // "this" score is better than recursive
            return true;
        }
        else {
            // no match
            return false;
        }
    }



    static bool fuzzy_match(char const* pattern, char const* str, int& outScore, uint8_t* matches, int maxMatches) {
        int recursionCount = 0;
        int recursionLimit = 10;

        return fuzzy_internal::fuzzy_match_recursive(pattern, str, outScore, str, nullptr, matches, maxMatches, 0, recursionCount, recursionLimit);
    }

    // Public interface
    bool fuzzy_match_simple(char const* pattern, char const* str) {
        while (*pattern != '\0' && *str != '\0') {
            if (tolower(*pattern) == tolower(*str))
                ++pattern;
            ++str;
        }

        return *pattern == '\0' ? true : false;
    }

    bool fuzzy_match(char const* pattern, char const* str, int& outScore) {

        uint8_t matches[256];
        return fuzzy_match(pattern, str, outScore, matches, sizeof(matches));
    }

    static bool sortbysec_desc(const std::pair<int, int>& a, const std::pair<int, int>& b)
    {
        return (b.second < a.second);
    }

	static void go_up(int* selecter) 
	{
		*selecter = *selecter > 0 ? *selecter - 1 : *selecter;
	}

	static void go_down(int* selecter, int limit) 
	{
		*selecter = *selecter < limit ? *selecter + 1 : *selecter;
	}

    int ApplyFilter(int* selected_item, const char* pattern_buffer, const std::vector<std::string>& items)
    {
        ImGuiContext& g = *GImGui;

        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        const ImGuiStyle& style = g.Style;
        int items_count = items.size();

        // Call the getter to obtain the preview string which is a parameter to BeginCombo()
        bool isNeedFilter = false;
        bool ShowFilter = false;
        bool value_changed = false;
		int show_count = 0;
		{

            if (pattern_buffer[0] != '\0') {
                isNeedFilter = true;
            }

			
			std::vector<std::pair<int, int> > itemScoreVector;
			if (isNeedFilter)
			{
				for (int i = 0; i < items_count; i++)
				{
					int score = 0;
					bool matched = fuzzy_match(pattern_buffer, items[i].c_str(), score);
					if (matched)
						itemScoreVector.push_back(std::make_pair(i, score));
				}
				std::sort(itemScoreVector.begin(), itemScoreVector.end(), sortbysec_desc);
			}

			show_count = isNeedFilter ? itemScoreVector.size() : items_count;
			ShowFilter = show_count > 0 && pattern_buffer[0] != '\0';
			
			// hotkeys
			if (ShowFilter) {

				if (IsKeyPressed(ImGuiKey_Tab)) {
					if (g.IO.KeyShift)
						go_up(selected_item);
					else
						go_down(selected_item, show_count - 1);
				}

				if (IsKeyPressed(ImGuiKey_UpArrow))
					go_up(selected_item);

				if (IsKeyPressed(ImGuiKey_DownArrow))
					go_down(selected_item, show_count - 1);
			}

			if (ShowFilter && ImGui::ListBoxHeader("##ComboWithFilter_itemList", show_count))
			{
				for (int i = 0; i < show_count; i++)
				{
					int idx = isNeedFilter ? itemScoreVector[i].first : i;
					PushID((void*)(intptr_t)idx);
					const bool item_selected = (idx == *selected_item);
					const char* item_text = items[idx].c_str();
					if (Selectable(item_text, item_selected)) {
						value_changed = true;
						*selected_item = idx;
					}
					PopID();
				}
				ImGui::ListBoxFooter();
			}			
        }


        if (value_changed)
            MarkItemEdited(g.LastItemData.ID);

        return pattern_buffer[0] == '\0' ? 0 : show_count;
    }
}
