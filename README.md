# FileRestrictionApp

## Introduction
FileRestrictionApp is a C++ application designed to restrict copy, paste, drag, and drop operations within a specified folder. The application ensures that no content can be copied into or out of the restricted folder.

## Features
- Restricts clipboard operations involving the restricted folder.
- Intercepts file drag and drop operations.
- Notifies the user when an operation is restricted.

## Getting Started

### Prerequisites
- Visual Studio (with C++ development tools)
- Git for Windows

### Installation

1. **Clone the repository**:
    ```bash
   https://github.com/Geeg-On-Hub/C_A.git
    ```
2. **Open the project in Visual Studio**:
    - Open Visual Studio.
    - Go to `File` > `Open` > `Project/Solution` and select the `.sln` file in the cloned repository.
    - Edit this folder location with your folder.
     - main.cpp

       ```bash
       const std::string rootFolder ="C:\\Users\\mtcro\\Desktop\\New folder"
        ```

### Building the Application

1. **Build the project**:
    - Press `Ctrl+Shift+B` to build the project.

### Running the Application

1. **Run the project**:
    - Press `Ctrl+F5` to run the project without debugging.

### Usage

- The application will monitor clipboard and file operations and restrict any involving the specified folder.
- You will receive a notification when an operation is restricted.

## Code Structure

- **ClipboardMonitor**: Manages clipboard monitoring and restriction.
- **FileSystemMonitor**: Intercepts and manages file system operations like drag and drop.
- **Validation**: Contains functions to validate paths.
- **Notification**: Manages user notifications.
- **Main.cpp**: Initializes and starts the monitors.

## Contributing

1. **Fork the repository**.
2. **Create a new branch**: `git checkout -b feature-branch`.
3. **Make your changes and commit them**: `git commit -m 'Add feature'`.
4. **Push to the branch**: `git push origin feature-branch`.
5. **Open a pull request**.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

