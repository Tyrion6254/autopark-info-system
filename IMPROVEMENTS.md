Planned Improvements
1. Crossplatform Desktop & Web GUI
Implementation method:

Desktop: Qt (C++) for a cross-platform graphical user interface.

Web: HTML/CSS/JS (React or Vue) + REST API.

2. SQL instead of .txt
Implementation method:

SQLite or PostgreSQL using C++ libraries (e.g., SQLiteCpp, libpqxx).

ORM (Object-Relational Mapping) — e.g., SOCI or ODB.

3. RESTful API
Implementation method:

C++ framework: Pistache, Crow, or cpprestsdk.

Structure: separate endpoints for vehicles, repairs, staff, etc.

4. Testing
Implementation method:

GoogleTest or Catch2 for unit and integration testing.

5. Data Visualization
Implementation method:

Python + matplotlib or seaborn to generate graphs (passenger flow, repairs).

Alternatively: integration in web via ECharts or Chart.js.

6. Authorization and Security
Implementation method:

Role-based access control (admin, mechanic, driver).

JSON Web Tokens (JWT) or OAuth2 for secure web access.

7. Full CRUD + Undo/Redo
Implementation method:

Change history logic using the Command Pattern.

Add change buffer and undo/redo functionality.

8. Logging and Auditing
Implementation method:

Log file or database table to track user actions.

Use logging libraries like spdlog or Boost.Log.

9. Documentation and Releases
Implementation method:

Swagger / OpenAPI for REST API documentation.

Markdown user manual.

GitHub Releases with binaries and changelog.