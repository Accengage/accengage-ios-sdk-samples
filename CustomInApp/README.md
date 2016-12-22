<p align="center" >
    <img src=".github/accengage.png?raw=true" alt="Accengage logo" title="Accengage logo"> 
</p>

![Platform](https://img.shields.io/badge/platform-iOS-lightgrey.svg?style=flat)
![Target](https://img.shields.io/badge/target-iOS%209+-blue.svg?style=flat)
![Devices](https://img.shields.io/badge/devices-iPhone-lightgrey.svg?style=flat)

Accengage In-App Notifications enables you to create rich and customizable in-app notifications. This project demonstrates how to create and configure fully customizable In-App Notifications using the **Additional display parameters**.

<br/>
<p align="center" >
  <img src=".github/screenshot_1.png?raw=true" alt="Screenshot 1" title="Screenshot 1">
  &nbsp;
  <img src=".github/screenshot_2.gif?raw=true" alt="Screenshot 2" title="Screenshot 2"> 
  &nbsp;
  <img src=".github/screenshot_3.png?raw=true" alt="Screenshot 3" title="Screenshot 3"> 
  
</p>
<br/>

# Usage

To ensure a good and a smooth usage of this sample, there are a few important steps that you need to take.

1. Configuration file

  Complete the **AccengageConfig.plist** with your own `partner id` and `private key`.

2. Add a new In-App template
  
  In your application target you need to add a new In-App template. From the Settings panel press the :heavy_plus_sign: in the right of the **INAPP TEMPLATES**. When prompted, complete the fields with the next values:
  
  |                 |                                                     |
  |-----------------|-----------------------------------------------------|
  | Name            | Customizable Text Interstitial                      |
  | Value           | CustomizableTextInterstitial                        |
  | Type            | :white_large_square: Banner :white_check_mark: Text |
  | Message display | :white_check_mark:                                  |
  | Landing page    | :white_large_square:                                |
  | Interstitial    | :white_check_mark:                                  |
  |                 |                                                     |

  <p align="center" ><img src=".github/add_new_tempalte.gif?raw=true" alt="Accengage logo" title="Accengage logo"></p>

3. Create your segment

4. Create the In-App Notification

# Customising the appearance

In order to customise the In-App appearance, you can play with the attributes of each customizable object.

## Customizable objects
<p align="center" ><img src=".github/diagram.png?raw=true" alt="Diagram" title="Diagram"></p>

| Object          |       Id     |    Type     |
|-----------------|--------------|-------------|
| Container       | container    |   view      |
| Header Image    | header.img   |   image     |
| Icon Image      | icon.img     |   image     |
| Title           | title        |   label     |
| Subtitle        | subtitle     |   label     |
| Body            | body         |   label     |
| Left Button     | left.btn     |   button    |
| Right Button    | right.btn    |   button    |
| Bottom Button   | bottom.btn   |   button    |
| Close Button    | close.btn    |   button    |

## Customizable objects attributes

IMPORTANT:heavy_exclamation_mark: If a required attribute is missing the related view will be removed.

### Common attributes
| Common attributes | Description                         |
|-------------------|-------------------------------------|
| bg.color          | The background.                     |
| border.color      | The border color                    |
| border.width      | The border width                    |
| border.radius     | The corner radius                   |
| hidden            | If added the related object will be removed from the super view |

### Label attributes
| Label attributes  | Description                         | Required |
|-------------------|-------------------------------------|----------|
| text              | Specifies the content of the label. |     :white_check_mark:    |
| color             | The text color.                     |          |

### Button attributes 
| Button attributes | Description                         | Required |
|-------------------|-------------------------------------|----------|
| text              | Specifies the title of the button.  |     :white_check_mark:   except for Close Button |
| color             | The text color.                     |          |
| action.type       | The buttom action                   |          |
| action.value      | The action's value                  |          |
| action.extra      | The action's extra parameters       |          |

### Image attributes 
| Image attributes  | Description             |     Required       |
|-------------------|-------------------------|--------------------|
| url               | The image URL or name   | :white_check_mark: |

# Actions

## Types
| Action type       | Description                                   |
|-------------------|-----------------------------------------------|
| udi               | Execute `Accengage updateDeviceInfo:`         |
| url               | Open an URL with `UIApplication openURL:`     |
| event             | Execute `Accengage trackEvent:withParameters:`|
| request           | Send an async GET request                      |

## Examples

### UDI 
To update a `custom_field` with the value `new_value` when the clic on the left button:

| Additional display parameters KEY | Additional display parameters VALUE | 
|------------------------------------|-------------------------------------|
| left.btn.action.type               | udi                                 |
| left.btn.action.value              | custom_field                        |
| left.btn.action.extra              | new_value                           |

The action will be: 

```
[Accengage updateDeviceInfo:@{@"custom_field": @"new_value"}]
```

### Event 
To trigger an Event with a type `1050` and extra param `auth` when the clic on the left button:

| BAdditional display parameters KEY | Additional display parameters VALUE | 
|------------------------------------|-------------------------------------|
| left.btn.action.type               | event                               |
| left.btn.action.value              | 1050                                |
| left.btn.action.extra              | auth                                |

The action will be: 

```
[Accengage trackEvent:1050 withParameters:@[@"auth"]];
```

### URL 
To open an URL when the clic on the left button:

| Additional display parameters KEY | Additional display parameters VALUE | 
|------------------------------------|-------------------------------------|
| left.btn.action.type               | url                                 |
| left.btn.action.value              | myapp://home/                       |

The action will be: 

```
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"myapp://home/"]];
```

# Usage examples

## Example 1
<p align="center" ><img src=".github/example_1.png?raw=true" alt="Diagram" title="Diagram"></p>

## Example 2
<p align="center" ><img src=".github/example_2.png?raw=true" alt="Diagram" title="Diagram"></p>
