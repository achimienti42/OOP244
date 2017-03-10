#ifndef SICT_ENROLLMENT_H
#define SICT_ENROLLMENT_H
#define _CRT_SECURE_NO_WARNINGS


namespace sict {
	class Enrollment{
	private:
		char name_[31];
		char code_[11];
		int year_;
		int semester_;
		int slot_;
		bool enrolled_;
	public:


		void display(bool nameOnly = false)const;
		bool isValid()const;
		void setEmpty();
		bool isEnrolled() const;
		void set(const char* name, const char* code, int year, int semester, int time, bool enrolled = false);
		bool hasConflict(const Enrollment &other) const;
		Enrollment();
		Enrollment(const char* name, const char* code, int year, int semester, int time);

	};
  }

#endif