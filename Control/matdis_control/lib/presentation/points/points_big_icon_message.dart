import 'package:flutter/material.dart';

class PointsBigIconMessage extends StatelessWidget {
  final String message;
  final IconData messageIcon;
  const PointsBigIconMessage(
      {super.key, required this.message, this.messageIcon = Icons.error});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);

    return Center(
      child: Material(
        color: Colors.black54,
        elevation: 10,
        borderRadius: const BorderRadius.all(Radius.circular(30)),
        child: FractionallySizedBox(
          widthFactor: 0.95,
          heightFactor: 0.95,
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Icon(
                messageIcon,
                size: 150,
                color: Colors.redAccent,
              ),
              const SizedBox(
                height: 20,
              ),
              Text(
                message,
                style: themeData.textTheme.displayLarge,
                textAlign: TextAlign.center,
              )
            ],
          ),
        ),
      ),
    );
  }
}
