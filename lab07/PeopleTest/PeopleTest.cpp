#include "stdafx.h"
#include "../People/CPupil.cpp"
#include "../People/CStudent.cpp"
#include "../People/CAdvancedStudent.cpp"
#include "../People/CTeacher.cpp"
#include "../People/CWorker.cpp"

struct Pupil
{
	const std::string name = "Masha";
	const std::string surname = "Ivanova";
	const std::string middleName = "Alexandrovna";
	const std::string address = "Petrova 16 A";
	const std::string schoolName = "School 28";
	const std::string schoolClass = "7b";
	CPupil pupil;
	Pupil()
		: pupil(name, surname, middleName, address, schoolName, schoolClass)
	{}
};

TEST_CASE_METHOD(Pupil, "Return information of pupil")
{
	SECTION("name")
	{
		REQUIRE(pupil.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(pupil.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(pupil.GetMiddleName() == middleName);
	}
	SECTION("address")
	{
		REQUIRE(pupil.GetAddress() == address);
	}
	SECTION("school name ")
	{
		REQUIRE(pupil.GetSchoolName() == schoolName);
	}
	SECTION("school class")
	{
		REQUIRE(pupil.GetSchoolClass() == schoolClass);
	}
}

struct Student
{
	const std::string name = "Masha";
	const std::string surname = "Ivanova";
	const std::string middleName = "Alexandrovna";
	const std::string address = "Petrova 16 A";
	const std::string universityName = "PGTU";
	const size_t studentTicketNumber = 1160501128;
	CStudent student;
	Student()
		: student(name, surname, middleName, address, universityName, studentTicketNumber)
	{}
};

TEST_CASE_METHOD(Student, "Return information of student")
{
	SECTION("name")
	{
		REQUIRE(student.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(student.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(student.GetMiddleName() == middleName);
	}
	SECTION("address")
	{
		REQUIRE(student.GetAddress() == address);
	}
	SECTION("school name")
	{
		REQUIRE(student.GetUniversityName() == universityName);
	}
	SECTION("school class")
	{
		REQUIRE(student.GetStudentTicketNumber() == studentTicketNumber);
	}
}

struct AdvancedStudent
{
	const std::string name = "Masha";
	const std::string surname = "Ivanova";
	const std::string middleName = "Alexandrovna";
	const std::string address = "Petrova 16 A";
	const std::string universityName = "PGTU";
	const size_t studentTicketNumber = 1160501128;
	const std::string dissertationTopic = "Quantum computer";
	CAdvancedStudent advancedStudent;
	AdvancedStudent()
		: advancedStudent(name, surname, middleName, address, universityName, studentTicketNumber, dissertationTopic)
	{}
};

TEST_CASE_METHOD(AdvancedStudent, "Return information of advanced student")
{
	SECTION("name")
	{
		REQUIRE(advancedStudent.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(advancedStudent.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(advancedStudent.GetMiddleName() == middleName);
	}
	SECTION("address")
	{
		REQUIRE(advancedStudent.GetAddress() == address);
	}
	SECTION("university name")
	{
		REQUIRE(advancedStudent.GetUniversityName() == universityName);
	}
	SECTION("student ticket number")
	{
		REQUIRE(advancedStudent.GetStudentTicketNumber() == studentTicketNumber);
	}
	SECTION("dissertation topic")
	{
		REQUIRE(advancedStudent.GetDissertationTopic() == dissertationTopic);
	}
}

struct Teacher
{
	const std::string name = "Masha";
	const std::string surname = "Ivanova";
	const std::string middleName = "Alexandrovna";
	const std::string address = "Petrova 16 A";
	const std::string subjectName = "OOP";
	CTeacher teacher;
	Teacher()
		: teacher(name, surname, middleName, address, subjectName)
	{}
};

TEST_CASE_METHOD(Teacher, "Return information of teacher")
{
	SECTION("name")
	{
		REQUIRE(teacher.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(teacher.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(teacher.GetMiddleName() == middleName);
	}
	SECTION("address")
	{
		REQUIRE(teacher.GetAddress() == address);
	}
	SECTION("subject name")
	{
		REQUIRE(teacher.GetSubjectName() == subjectName);
	}
}

struct Worker
{
	const std::string name = "Masha";
	const std::string surname = "Ivanova";
	const std::string middleName = "Alexandrovna";
	const std::string address = "Petrova 16 A";
	const std::string specialty = "Programming Engineer";
	CWorker worker;
	Worker()
		: worker(name, surname, middleName, address, specialty)
	{}
};

TEST_CASE_METHOD(Worker, "Return information of worker")
{
	SECTION("name")
	{
		REQUIRE(worker.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(worker.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(worker.GetMiddleName() == middleName);
	}
	SECTION("address")
	{
		REQUIRE(worker.GetAddress() == address);
	}
	SECTION("specialty")
	{
		REQUIRE(worker.GetSpecialty() == specialty);
	}
}